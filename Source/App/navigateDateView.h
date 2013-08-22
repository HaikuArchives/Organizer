#ifndef _navigateDateView_h_
#define _navigateDateView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class NavigateDateView
		: public BView
{
public:
						NavigateDateView(BRect frame, const char *name, uint32 resizeMask, uint32 flags);
						~NavigateDateView();
	virtual void		MessageReceived(BMessage *message);
	void				Draw(BRect update);
		
	BMenu			*	mMenuYear;
	BMenu			*	mMenuMonth;
	BMenuItem		*	mMenuItem;
	BMenuField		*	mMenuFieldYear;
	BMenuField		*	mMenuFieldMonth;

private:

	BString				tmp;
	BString				tmp2;
};

#endif

