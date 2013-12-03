//-----------------------  Local includes  ----------------------
#include "calenderView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

//---------------------------------------------------------------
CalenderView::CalenderView(BRect frame, const char *name, uint32 resizeMask, uint32 flags)
		: BView(frame, name, resizeMask, flags)
{
SetViewColor(BeBack);

//We want the correct language!!!!
BString tmp;
	switch (INT_LANGUAGE)
	{
	case 0:
	mCalender = new MCalender(BRect(0, 0, 500, 500), "mCalender", STR_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER),
							2002, 10, 17, BOOL_COLORFUL_CALENDER, BOOL_AMERICAN_STYLE, M_ENGLISH, B_FOLLOW_LEFT | B_FOLLOW_TOP,
							B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
	break;
	case 1:
	mCalender = new MCalender(BRect(0, 0, 500, 500), "mCalender", STR_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER),
							2002, 10, 17, BOOL_COLORFUL_CALENDER, BOOL_AMERICAN_STYLE, M_NORWEGIAN, B_FOLLOW_LEFT | B_FOLLOW_TOP,
							B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
	break;
	case 2:
	mCalender = new MCalender(BRect(0, 0, 500, 500), "mCalender", STR_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER),
							2002, 10, 17, BOOL_COLORFUL_CALENDER, BOOL_AMERICAN_STYLE, M_SPANISH, B_FOLLOW_LEFT | B_FOLLOW_TOP,
							B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
	break;
	case 3:
	mCalender = new MCalender(BRect(0, 0, 500, 500), "mCalender", STR_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER),
							2002, 10, 17, BOOL_COLORFUL_CALENDER, BOOL_AMERICAN_STYLE, M_GERMAN, B_FOLLOW_LEFT | B_FOLLOW_TOP,
							B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
	break;
	case 4:
	mCalender = new MCalender(BRect(0, 0, 500, 500), "mCalender", STR_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER),
							2002, 10, 17, BOOL_COLORFUL_CALENDER, BOOL_AMERICAN_STYLE, M_GENERIC, B_FOLLOW_LEFT | B_FOLLOW_TOP,
							B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
	break;
	default:
	mCalender = new MCalender(BRect(0, 0, 500, 500), "mCalender", STR_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER),
							2002, 10, 17, BOOL_COLORFUL_CALENDER, BOOL_AMERICAN_STYLE, M_ENGLISH, B_FOLLOW_LEFT | B_FOLLOW_TOP,
							B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
	break;
	}
mCalender->SetBoxWidthAndHeight(60, 60);
mCalender->SetYear(mCalender->ThisYear());
mCalender->SetMonth(mCalender->ThisMonth());
mCalender->SetDay(mCalender->ThisDay());

//Load Settings
MSave load("load");

find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
String.SetTo(Path.Path());
String.Append(SAVE_SETTINGS_PATH);
Path.SetTo(String.String());

load.FindBool(Path, SAVE_FILE_NAME, NAME_CALENDER_STYLE, &Bool, false);
mCalender->SetAmericanStyleCalender(Bool);
load.FindBool(Path, SAVE_FILE_NAME, NAME_CALENDER_COLORFUL, &Bool, true);
mCalender->SetColorfulCalender(Bool);

AddChild(mCalender);
be_app->PostMessage(MSG_GET_NOTES);
}

//---------------------------------------------------------------
CalenderView::~CalenderView()
{

}

//---------------------------------------------------------------
void CalenderView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}

//---------------------------------------------------------------
void CalenderView::Draw(BRect update)
{

}


