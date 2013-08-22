// OpenGL tutorial view object
//
// This is where all the OpenGL stuff gets done; a view with a separate
// drawing thread.

#ifndef OpenGL_View_h
#define OpenGL_View_h

#include <opengl/GLView.h>
#include <kernel/OS.h>
#include "../Constants.h"

class BBitmap;
class Wind;

class TutGLView : public BGLView
{
public:
	TutGLView( Wind *owner, BRect frame, const char *name, int32 mode, int32 flags );
	virtual ~TutGLView( void );

	// Override BView methods:
	virtual void AttachedToWindow( void );
	virtual void FrameResized( float width, float height );
	virtual void KeyDown( const char *bytes, int32 size );

	// Override BGLView method:
	virtual void ErrorCallback( GLenum err );

	// Our own method for rendering.
	void Render( void );

private:
	// Private methods; these correspond to the usual OpenGL application's
	// init/reshape/draw functions.
	void gInit( void );
	void gReshape( int width, int height );
	void gDraw( void );

	GLfloat pad_x;	// x axis of pad
	GLfloat pad_y;	// y axis of pad
	
	GLfloat circle_x;	// x axis of pad
	GLfloat circle_y;	// y axis of pad
	
	bool circle_moving_up;
	bool circle_moving_right;
	
	bool quit;
	
	GLfloat circle_movement_speed_y;
	GLfloat circle_movement_speed_x;
	
	GLfloat circle_movement_speed_x_standard;
	/*
	GLfloat rquad;	// angle for the quad
	GLfloat tilt;
	GLfloat zoom;
	GLfloat rotate;
	*/

	// Load and fix a texture bitmap.  Caller deletes the returned bitmap,
	// which is unsuitable for use in DrawBitmap*() calls.
	BBitmap *LoadTexture( const char *tex_name );

	// My parent window
	Wind *_window;
};

#endif
