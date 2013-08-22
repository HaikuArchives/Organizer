// see TutGLView.h
//
// This is where all the OpenGL stuff gets done; a view with a separate
// drawing thread.

#include "glView.h"
#include "glWindow.h"

#include <opengl/GL/gl.h>
#include <opengl/GL/glu.h>
#include <app/Application.h>
#include <interface/InterfaceDefs.h>
#include <interface/Bitmap.h>
#include <translation/TranslationUtils.h>
#include <kernel/OS.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

// ----------------------------------------------------------------------
// Constructor/destructor
TutGLView::TutGLView( Wind *owner_wind, BRect frame, const char *name, 
					  int32 mode, int32 flags )
	: BGLView( frame, const_cast<char *>( name ), mode, flags, 
			   BGL_RGB | BGL_DOUBLE | BGL_DEPTH ),
	  pad_x( 1.0 ),
	  pad_y(-2.0),
	  circle_x(1.0),
	  circle_y(1.0),
	  circle_moving_up(true),
	  circle_moving_right(false),
	  circle_movement_speed_y(0.1),
	  circle_movement_speed_x(0.1),
	  circle_movement_speed_x_standard(0.1),
	  _window(owner_wind )
{
	EnableDirectMode( false );
	quit = false;
}

TutGLView::~TutGLView( void )
{
}

void TutGLView::AttachedToWindow( void )
{
	// Make keyboard/mouse input go to this view when its window has
	// focus (that'll stay in effect until another view calls MakeFocus()
	// or the user puts the focus on a control... which won't happen in
	// this app because there are no other views and no controls).
	MakeFocus();

	// Initialize OpenGL; gInit() sets things up, gReshape() makes sure
	// OpenGL knows about the view's size/shape.
	LockGL();
	BGLView::AttachedToWindow();
	gInit();
	BRect r = Bounds();
	gReshape( r.IntegerWidth(), r.IntegerHeight() );
	UnlockGL();
}

void TutGLView::FrameResized( float width, float height )
{
	// When the view is resized (it follows the window, since we created
	// it with B_FOLLOW_ALL_SIDES), we need to tell OpenGL that it's
	// rendering into a new size/shape.
	LockGL();
	BGLView::FrameResized( width, height );
	gReshape( width, height );
	UnlockGL();
	Render();
}

void TutGLView::KeyDown( const char *bytes, int32 size )
{
	// We want to exit when the user presses Esc (Alt-Q will also work,
	// automatically); otherwise we pass the key press off to our parent
	// class when it's not handled.  Alt-F will also toggle fullscreen mode,
	// but that's handled by the window.

	// You can add other keyboard commands in here, or between this and
	// the BGLView::KeyDown() at the bottom, it doesn't matter.
	if( size == 1 ) {
		switch( bytes[0] ) {
		case B_ESCAPE:
			be_app->PostMessage( B_QUIT_REQUESTED );
			return;
			break;
		case B_UP_ARROW:
			
		break;

		case B_DOWN_ARROW:
			
		break;

		case B_LEFT_ARROW:
				if (pad_x > -1.8)
				{
				pad_x -= 0.2;
				}
		break;
			
		case B_RIGHT_ARROW:
				if (pad_x < 3.9)
				{
				pad_x += 0.2;
				}
		break;
		case B_ENTER:
			
		break;
		case B_BACKSPACE:
			
		break;
		default:
			break;
		}
	}

	BGLView::KeyDown( bytes, size );
}

void TutGLView::ErrorCallback( GLenum err )
{
	// The ErrorCallback() method is called whenever OpenGL has a problem;
	// you can override it to ignore specific known error messages and
	// display otheres, abort the program, etc... we'll just print them
	// out.  You'll have to run the application from a Terminal to see
	// these.
	fprintf( stderr, "Unexpected error occured (%ld):\n", err );
	fprintf( stderr, "\t%s\n", gluErrorString( err ) );
}

void TutGLView::Render( void )
{
	// Render our OpenGL scene and swap the buffer so we can actually see
	// it.
	LockGL();
	gDraw();
	if( _window->draw_mutex->Lock() ) {
		if( _window->window_connected ) SwapBuffers();
		_window->draw_mutex->Unlock();
	}
	UnlockGL();
}

void TutGLView::gInit( void )
{
	// Set up our OpenGL context.
	
	// Clear to black
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	
	// Set up the depth buffer
	glClearDepth( 1.0 );
	glDepthFunc( GL_LESS );
	glEnable( GL_DEPTH_TEST );
	
	// Set up perspective view
	glShadeModel( GL_SMOOTH );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	BRect r = Bounds();
	gluPerspective( 45.0, r.Width() / r.Height(), 0.1, 100.0 );
	glMatrixMode( GL_MODELVIEW );
}

void TutGLView::gReshape( int width, int height )
{
	// The OpenGL view has been resized, so we have to reconfigure our
	// OpenGL context to reflect that.

	if( height == 0 ) height = 1;	// prevent divide-by-zero
	
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0, (float)width/(float)height, 0.1, 100.0 );
	glMatrixMode( GL_MODELVIEW );
}

void TutGLView::gDraw( void )
{
	if (quit)
	{
	be_app->PostMessage(MSG_CLOSE_GL_GAME);
	}
	// The actual OpenGL scene.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	// Move Left 1.5 units, and 6.0 units into the screen.
	glTranslatef( -1.5, 0.0, -6.0 );
	
	//Draw the Circle
	glBegin( GL_QUADS );
		glVertex3f(circle_x, circle_y, 0.0);
		glVertex3f(circle_x + 0.5, circle_y, 0.0);
		glVertex3f(circle_x + 0.5, circle_y - 0.5, 0.0);
		glVertex3f(circle_x, circle_y - 0.5, 0.0);
	glEnd();
	
	// Create two Squares (the pad).
	glColor3f( 1.0, 1.0, 1.0 );	
	glBegin( GL_QUADS );
		glColor3f( 1.0, 0.0, 0.0 );	
		glVertex3f( pad_x, 			pad_y + 0.1, 	0.0 );	// top
		glVertex3f( pad_x + 0.8, 	pad_y + 0.1, 	0.0 );	// bottom-right
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( pad_x + 0.8, 	pad_y, 			0.0 );	// bottom-left
		glVertex3f( pad_x, 			pad_y, 			0.0 );	// bottom-left
	glEnd();
	glBegin( GL_QUADS );
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( pad_x, 			pad_y, 			0.0 );	// top
		glVertex3f( pad_x + 0.8, 	pad_y, 			0.0 );	// bottom-right
		glColor3f( 1.0, 0.0, 0.0 );	
		glVertex3f( pad_x + 0.8, 	pad_y - 0.1, 	0.0 );	// bottom-left
		glVertex3f( pad_x, 			pad_y - 0.1, 	0.0 );	// bottom-left
	glEnd();
	
	//Calculate the circle
		//Moving up
		if (circle_moving_up)
		{
			if (circle_y > 2.5)
			{
			circle_y -= circle_movement_speed_y;
			circle_moving_up = false;
			}
			else
			{
			circle_y += circle_movement_speed_y;
			}
		
		}
		//Moving down
		else
		{
			if (circle_y < -2.0)
			{
			//Explode
			glBegin( GL_LINES );
				glColor3f( 1.0, 1.0, 0.0 );
				glVertex3f( circle_x, pad_y, 0.0 );
				glVertex3f( circle_x - 0.1, -1, 0.0 );
				
				glColor3f( 1.0, 0.0, 0.0 );
				glVertex3f( circle_x, pad_y, 0.0 );
				glVertex3f( circle_x + 0.4, -1.5, 0.0 );
				
				glColor3f( 0.8, 1.0, 0.0 );
				glVertex3f( circle_x, pad_y, 0.0 );
				glVertex3f( circle_x - 0.3, -1, 0.0 );
				
				glColor3f( 0.8, 0.5, 0.0 );
				glVertex3f( circle_x, pad_y, 0.0 );
				glVertex3f( circle_x + 0.2, -1.1, 0.0 );
				
			glEnd();
			circle_movement_speed_x = 0;
			quit = true;
			}
			else
			{
			circle_y -= circle_movement_speed_y;
			}
		}
		//Moving right
		if (circle_moving_right)
		{
			if (circle_x > 4.3)
			{
			circle_x -= circle_movement_speed_x;
			circle_moving_right = false;
			}
			else
			{
			circle_x += circle_movement_speed_x;
			}
		
		}
		//Moving left
		else
		{
			if (circle_x < -1.95)
			{
			circle_x += circle_movement_speed_x;
			circle_moving_right = true;
			}
			else
			{
			circle_x -= circle_movement_speed_x;
			}
		}
	
		//Hit pad
		if (circle_x > pad_x - 0.30 && circle_x < pad_x + 0.7)
		{	
			//Correct height
			if (circle_y < -1.4 && circle_y > -1.70)
			{
			circle_moving_up = true;
				/*
				//Left side
				if (circle_x > pad_x - 0.30 && circle_x > pad_x - 0.10)
				{
					if (circle_moving_right)
					{
					circle_movement_speed_x += 0.1;
					}
					else
					{
					circle_movement_speed_x -= 0.1;
					}
				}
				
				//Right side
				if (circle_x > pad_x + 0.6 && circle_x < pad_x + 0.7)
				{
					if (circle_moving_right)
					{
					circle_movement_speed_x += 0.09;
					}
					else
					{
					circle_movement_speed_x -= 0.09;
					}
				}
				*/
			}
			
			
		}
	//circle_y += 0.05;
}

// ----------------------------------------------------------------------
// Load a bitmap and fix it up for use as a texture bitmap, which is
// unsuitable for use in DrawBitmap*() calls due to differences in the
// BeOS and OpenGL co-ordinate systems.
//
// Caller owns the returned bitmap, LoadTexture() returns NULL if the bitmap
// isn't suitable (only handles 32-bit images).

BBitmap *TutGLView::LoadTexture( const char *tex_name )
{
	// NOTE: This replaces auxDIBImageLoad() in the original!
	BBitmap *bits = BTranslationUtils::GetBitmap( tex_name );
	if( !bits ) return bits;

	// We'll only deal with 32-bit textures, because we're lazy.
	// If you're not lazy, you could convert the bitmap here, or
	// add more colour space handlers below where we make the texture
	// with glTexImage2D().
	if( bits->ColorSpace() != B_RGBA32 && bits->ColorSpace() != B_RGB32 ) {
    	delete bits;
    	return NULL;
    }

	// BeOS bitmaps have 0,0 in the top-left; OpenGL expects them in the
	// lower-left.  Dang.
	//
	// Note that this isn't going to behave if you've got an odd number of
	// rows in the bitmap.  Then again, you won't be able to use that as an
	// OpenGL texture.
	bits->Lock();

	int32 bpr = bits->BytesPerRow();

	char *top = static_cast<char *>( bits->Bits() );
	char *bottom = top + bits->Bounds().IntegerHeight() * bpr;

	char *tmp_bytes = new char[bpr];
	while( top < bottom ) {
		// Save a line into the temp buffer.
		memcpy( tmp_bytes, bottom, bpr );

#if 0
		// The way we'd like to do it:
		memcpy( bottom, top, bpr );
		memcpy( top, tmp_bytes, bpr );
#else
		// The way we have to do it.  Why?  BBitmap and OpenGL don't
		// even agree on the order of bytes within an RGBA colour.  :-(
		rgb_color *b = (rgb_color *)( bottom );
		rgb_color *t = (rgb_color *)( top );
		for( int i = 0; i < ( bpr / 4 ); i++ ) {
			b->red = t->blue;
			b->green = t->green;
			b->blue = t->red;
			b->alpha = t->alpha;
			b++, t++;
		}
		t = (rgb_color *)( top );
		b = (rgb_color *)( tmp_bytes );
		for( int i = 0; i < ( bpr / 4 ); i++ ) {
			t->red = b->blue;
			t->green = b->green;
			t->blue = b->red;
			t->alpha = b->alpha;
			b++, t++;
		}
#endif
		bottom -= bpr;
		top += bpr;
	}

	bits->Unlock();

	return bits;
}
