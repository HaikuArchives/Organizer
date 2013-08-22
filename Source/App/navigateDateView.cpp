//-----------------------  Local includes  ----------------------
#include "navigateDateView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

// Local Defines ---------------------------------------------------------------

//---------------------------------------------------------------
NavigateDateView::NavigateDateView(BRect frame, const char *name, uint32 resizeMask, uint32 flags)
		: BView(frame, name, resizeMask, flags)
{
SetViewColor(BeBack);

//Year
mMenuYear = new BMenu(STR_YEAR[INT_LANGUAGE]);
//Add
	for (int a = 2000; a <= 2015; a++)
	{
	tmp.SetTo("");
	tmp << a;
	mMenuItem = new BMenuItem(tmp.String(), new BMessage(MSG_CHANGE_YEAR));
	mMenuYear->AddItem(mMenuItem);
		if (a == INT_YEAR)
		{
		mMenuItem->SetMarked(true);
		mMenuYear->SetName(tmp.String());
		}
	}

mMenuFieldYear = new BMenuField(BRect(10, 10, 120, 40), "mMenuField", STR_YEAR[INT_LANGUAGE], mMenuYear,
							 B_FOLLOW_LEFT | B_FOLLOW_TOP);
mMenuYear->SetLabelFromMarked(true);
mMenuFieldYear->SetDivider(40);
AddChild(mMenuFieldYear);

//Month
mMenuMonth = new BMenu(STR_MONTH[INT_LANGUAGE]);
//Add
	for (int b = 1; b <= 12; b++)
	{
	tmp.SetTo(STR_MONTHNAMES[b][INT_LANGUAGE]);
	mMenuItem = new BMenuItem(tmp.String(), new BMessage(MSG_CHANGE_MONTH));
	mMenuMonth->AddItem(mMenuItem);
		if (b == INT_MONTH)
		{
		mMenuItem->SetMarked(true);
		mMenuMonth->SetName(tmp.String());
		}
	}

mMenuFieldMonth = new BMenuField(BRect(140, 10, 260, 40), "mMenuField", STR_MONTH[INT_LANGUAGE], mMenuMonth,
							 B_FOLLOW_LEFT | B_FOLLOW_TOP);
mMenuMonth->SetLabelFromMarked(true);
mMenuFieldMonth->SetDivider(40);
AddChild(mMenuFieldMonth);

}

//---------------------------------------------------------------
NavigateDateView::~NavigateDateView()
{

}

//---------------------------------------------------------------
void NavigateDateView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}

//---------------------------------------------------------------
void NavigateDateView::Draw(BRect update)
{

}

