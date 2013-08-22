#ifndef _menuView_h_
#define _menuView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class MenuView
		: public BView
{
public:
						MenuView(BRect frame, const char *name, uint32 resizeMask, uint32 flags);
						~MenuView();
	virtual void		MessageReceived(BMessage *message);
	void				Draw(BRect update);

private:

	BMenuBar		*	mMenuBar;
	BMenu			*	mMenu;
	BMenuItem		*	mMenuItem;

};

#endif

