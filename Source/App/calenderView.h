#ifndef _calenderView_h_
#define _calenderView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class CalenderView
		: public BView
{
public:
						CalenderView(BRect frame, const char *name, uint32 resizeMask, uint32 flags);
						~CalenderView();
	virtual void		MessageReceived(BMessage *message);
	void				Draw(BRect update);
	MCalender		*	mCalender;

private:
	BPath 				Path;
	BString 			String;
	bool				Bool;
};

#endif

