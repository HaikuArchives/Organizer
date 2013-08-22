#ifndef _preferencesWindow_h_
#define _preferencesWindow_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"
#include "preferencesView.h"

//----------------------- Global includes  ----------------------


class PreferencesWindow
		 : public BWindow
{
public:
							PreferencesWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags);
							~PreferencesWindow();
	virtual void			MessageReceived(BMessage *message);
	virtual bool			QuitRequested();

	PreferencesView		*	_PreferencesView;
private:
	
};

#endif
