#ifndef _aboutWindow_h_
#define _aboutWindow_h_

//-----------------------  Local includes  ----------------------
#include "aboutView.h"
#include "Constants.h"

//----------------------- Global includes  ----------------------


class AboutWindow
		 : public BWindow
{
public:
						AboutWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags);
						~AboutWindow();
	virtual void		MessageReceived(BMessage *message);
	virtual bool		QuitRequested();

private:

	AboutView		*	_AboutView;
};

#endif
