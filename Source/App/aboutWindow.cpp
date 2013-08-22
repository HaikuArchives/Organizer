//-----------------------  Local includes  ----------------------
#include "aboutWindow.h"

//----------------------- Global includes  ----------------------


//---------------------------------------------------------------
AboutWindow::AboutWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags)
			 : BWindow(frame, title, B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL, B_NOT_RESIZABLE)
{
_AboutView = new AboutView(BRect(0, 0, 450, 400),"_AboutView", B_FOLLOW_TOP | B_FOLLOW_LEFT | B_FOLLOW_RIGHT, B_WILL_DRAW);

//MoveTo(300, 300);

AddChild(_AboutView);
}

//---------------------------------------------------------------
AboutWindow::~AboutWindow()
{

}

//---------------------------------------------------------------
void AboutWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}

//---------------------------------------------------------------
bool AboutWindow::QuitRequested()
{
	//return BWindow::Close();
}


