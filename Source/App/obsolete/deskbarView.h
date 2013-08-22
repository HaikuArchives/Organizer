#ifndef _DeskbarView_h_
#define _DeskbarView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class DeskbarView
		: public BView
{
public:
						DeskbarView();
						~DeskbarView();
	virtual void		MessageReceived(BMessage *message);
	void				Draw(BRect update);

private:
	
};

#endif

