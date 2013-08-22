#ifndef _aboutWindowView_h_
#define _aboutWindowView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class AboutView
		: public BView
{
public:
						AboutView(BRect frame, const char *name, uint32 resizeMask, uint32 flags);
						~AboutView();
	virtual void		MessageReceived(BMessage *message);
	void				Draw(BRect update);
	void				MouseDown(BPoint point);

private:

};

#endif

