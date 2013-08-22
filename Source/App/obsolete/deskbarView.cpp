//-----------------------  Local includes  ----------------------
#include "deskbarView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------
const rgb_color Gray = {219, 219, 219};
const rgb_color Red2 = {250, 0, 0};

//---------------------------------------------------------------
DeskbarView::DeskbarView()
		: BView(BRect(0, 0, 30, 30), "DeskbarView", B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW)
{
SetViewColor(Red2);

}

//---------------------------------------------------------------
DeskbarView::~DeskbarView()
{

}

//---------------------------------------------------------------
void DeskbarView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}

//---------------------------------------------------------------
void DeskbarView::Draw(BRect update)
{

}
