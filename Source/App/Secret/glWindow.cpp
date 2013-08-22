// see Wind.h
//
// Window object for NeHe's OpenGL tutorials; nice and simple.

#include "glView.h"
#include "glWindow.h"

#include <app/Application.h>
#include <interface/Alert.h>
#include <support/Locker.h>
#include <stdio.h>
#include <limits.h>

// ----------------------------------------------------------------------
// OpenGL drawing thread

int32 render_thread( void *data )
{
	// Create the variables we'll need up here so we don't waste time in
	// the draw loop.
	Wind *self = (Wind *)data;
	bigtime_t start_render, end_render, render_dt;
	bigtime_t snooze_time;
	status_t retval;

	while( !self->window_teardown ) {
		snooze_time = 1;

		if( self->window_connected ) {
			// Render and draw the OpenGL scene.
			self->total_frames++;

			start_render = system_time();
			self->view->Render();
			end_render = system_time();

			render_dt = end_render - start_render;

			if( render_dt > self->render_target ) self->targets_missed++;
			if( render_dt < self->render_target ) snooze_time = self->render_target - render_dt;

			if( render_dt < self->render_min ) self->render_min = render_dt;
			if( render_dt > self->render_max ) self->render_max = render_dt;
		}

		retval = acquire_sem_etc( self->snooze_sem, 1, B_RELATIVE_TIMEOUT, snooze_time );
		if( retval == B_BAD_SEM_ID || retval == B_INTERRUPTED ) break;
	}

	return B_OK;
}

// ----------------------------------------------------------------------
// Constructor and destructor

Wind::Wind( const char *title )
//	: BDirectWindow( BRect( 100.0, 100.0, 1123.0, 867.0 ),	// 1024x768
//	: BDirectWindow( BRect( 100.0, 100.0, 899.0, 699.0 ),	// 800x640
//	: BDirectWindow( BRect( 100.0, 100.0, 739.0, 579.0 ),	// 640x480
//	: BDirectWindow( BRect( 100.0, 100.0, 611.0, 483.0 ),	// 512x384
	: BDirectWindow( BRect( 100.0, 100.0, 499.0, 399.0 ),	// 400x300
			   		 title,
			   		 B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
			   		 B_ASYNCHRONOUS_CONTROLS | B_NOT_RESIZABLE | B_NOT_ZOOMABLE ),
	  view( NULL ),
	  draw_mutex( NULL ),
	  window_connected( false ),
	  window_teardown( false ),
	  window_dirty( true ),
	  draw_thread( -1 ),
	  snooze_sem( -1 ),
	  fps_target( 0.0 ),
	  render_target( 0 ),
	  render_min( LONGLONG_MAX ),
	  render_max( LONGLONG_MIN ),
	  targets_missed( 0 ),
	  total_frames( 0 )
{
	// Check to see if this works.
	if( !SupportsWindowMode() ) {
		BAlert *damn = new BAlert( "BDirectWindow Problems",
								   "Your video card driver doesn't support "
								   "BDirectWindow.  Please go complain to "
								   "Be, Inc. about that.\n"
								   "You won't be able to run this program "
								   "until you get an updated video driver.\n"
								   "Sorry.",
								   "Dang", NULL, NULL,
								   B_WIDTH_AS_USUAL,
								   B_STOP_ALERT );
		damn->Go();

		// Bail out
		be_app->PostMessage( B_QUIT_REQUESTED );
		return;
	}

	// Create a drawing mutex
	draw_mutex = new BLocker( "window draw mutex", true );

	// Create a snoozer semaphore.
	snooze_sem = create_sem( 0, "OpenGL snoozer sem" );
	if( snooze_sem < 0 ) {
		fprintf( stderr, "Can't create snoozing semaphore, bailing out...\n" );
		be_app->PostMessage( B_QUIT_REQUESTED );
		return;
	}

	// Default fps; this has to be called *after* the drawing mutex is
	// created, because it locks that mutex (so you can change the FPS
	// on the fly when you want to).
	SetFPS( 60.0 );

	// Start the drawing thread.
	draw_thread = spawn_thread( render_thread, 
								"OpenGL drawing thread",
								B_DISPLAY_PRIORITY,
								this );
	if( draw_thread < 0 ) {
		// Can't start the thread, that's bad...
		fprintf( stderr, "Can't spawn drawing thread, bailing out...\n" );
		be_app->PostMessage( B_QUIT_REQUESTED );
		return;
	}
	(void)resume_thread( draw_thread );

	// Add a shortcut so Alt-F will toggle fullscreen.
	AddShortcut( 'f', 0, new BMessage( GO_FULLSCREEN ) );

	// Create and add the OpenGL view, show the window, and render.
	view = new TutGLView( this,
						  Bounds(), "OpenGL view", 
						  B_FOLLOW_ALL_SIDES, 
						  B_WILL_DRAW | B_FRAME_EVENTS );
	AddChild( view );

	Show();
}

Wind::~Wind( void )
{
	// We're closing the window now...
	delete_sem( snooze_sem );
	delete draw_mutex;
	window_teardown = true;
	Hide();
	Sync();

	int32 retval = B_OK;
	//(void)wait_for_thread( draw_thread, &retval );
	kill_thread(draw_thread);
	// Print some info to the user...
	printf( "Frames/second target: %g\n", fps_target );
	printf( "  usecs/frame target: %Ld\n", render_target );
	printf( "       fastest frame: %Ld usec (%g fps)\n", render_min, ( 1000000.0 / (float)render_min ) );
	printf( "       slowest frame: %Ld usec (%g fps)\n", render_max, ( 1000000.0 / (float)render_max ) );
	printf( "# of too-slow frames: %Ld/%Ld (%g%%)\n", targets_missed, total_frames, ((float)targets_missed)/((float)total_frames) * 100.0 );
}

// ----------------------------------------------------------------------
// BWindow methods
bool Wind::QuitRequested( void )
{
//	kill_thread(draw_thread);
	//Close();
	//return(1);
}

void Wind::MessageReceived( BMessage *msg )
{
	switch( msg->what ) {
	case GO_FULLSCREEN:
		if( IsFullScreen() ) {
			SetFullScreen( false );
		} else {
			SetFullScreen( true );
		}
		break;

	default:
		BDirectWindow::MessageReceived( msg );
		break;
	}
}

// ----------------------------------------------------------------------
// BDirectWindow methods
void Wind::DirectConnected( direct_buffer_info *info )
{
	// Skip it if we're exitting.
	if( !window_connected && window_teardown ) return;

	draw_mutex->Lock();

	switch( info->buffer_state & B_DIRECT_MODE_MASK ) {
	case B_DIRECT_START:
		window_connected = true;
		// fall-through!

	case B_DIRECT_MODIFY:
		// Does BGLView take care of all this nonsense?
		window_dirty = true;
		break;

	case B_DIRECT_STOP:
		window_connected = false;
		break;
	}
	
	draw_mutex->Unlock();

	// Let the GL view do its thing.
	view->DirectConnected( info );
	if( window_connected ) {
		view->EnableDirectMode( true );
	} else {
		view->EnableDirectMode( false );
	}
}

// ----------------------------------------------------------------------
// Set the frames/second target and times

void Wind::SetFPS( float target )
{
	if( target < 0.0 ) {
		fprintf( stderr, "You set the frames/sec target negative: %g", target );
		target = -target;
	}

	// target of 0 means "draw once"
	if( target == 0.0 ) {
		draw_mutex->Lock();
		fps_target = target;
		render_target = 0;
		draw_mutex->Unlock();
		return;
	}

	// Now we calculate the number of microseconds each frame can take to
	// give us that FPS rating.
	//
	// 1 usecond is 1,000,000.0 of a second... there might be a bit of a
	// round-off error here, but a fraction of a microsecond is pretty fast.
	//
	// We use this extra temporary here to avoid locking the mutex for very
	// long... probably not necessary, but floating-point -> integer
	// conversions are notoriously expensive.
	bigtime_t the_target = (bigtime_t)( 1000000.0 / target );

	draw_mutex->Lock();
	fps_target = target;
	render_target = the_target;
	draw_mutex->Unlock();
}
