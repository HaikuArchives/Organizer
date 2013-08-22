// OpenGL tutorial window object
//
// Window object for NeHe's OpenGL tutorials; nice and simple.

#ifndef OpenGL_Wind_h
#define OpenGL_Wind_h

#include <game/DirectWindow.h>
#include <kernel/OS.h>
#include "../Constants.h"

class TutGLView;
class BLocker;

// OpenGL window messages
enum {
	GO_FULLSCREEN = 'gofu',
};

int32 render_thread( void *data );

class Wind : public BDirectWindow
{
public:
	Wind( const char *title );
	virtual ~Wind( void );

	// Override BWindow methods:
	virtual bool QuitRequested( void );
	virtual void MessageReceived( BMessage *msg );

	// Override BDirectWindow methods:
	virtual void DirectConnected( direct_buffer_info *info );

	void SetFPS( float target );

	// Pointer to our view object:
	TutGLView *view;

	// Direct window drawing bits...
	BLocker *draw_mutex;
	bool window_connected;
	bool window_teardown;
	bool window_dirty;

	thread_id draw_thread;
	sem_id snooze_sem;

	// Frames/sec. target and counters (converted)
	float fps_target;
	bigtime_t render_target;
	bigtime_t render_min;
	bigtime_t render_max;

	bigtime_t targets_missed;
	bigtime_t total_frames;
};

#endif
