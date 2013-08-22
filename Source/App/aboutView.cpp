//-----------------------  Local includes  ----------------------
#include "aboutView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

//---------------------------------------------------------------
AboutView::AboutView(BRect frame, const char *name, uint32 resizeMask, uint32 flags)
		: BView(frame, name, resizeMask, flags)
{
ForceFontAliasing(false);
}

//---------------------------------------------------------------
AboutView::~AboutView()
{

}

//---------------------------------------------------------------
void AboutView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}


//---------------------------------------------------------------
void AboutView::Draw(BRect update)
{
BString tempString;

//Draw Background
SetHighColor(DiscreetLightGray);
FillRect(Bounds());

SetHighColor(DiscreetGray);
FillRect(BRect(0, 0, Bounds().right, 20));

SetHighColor(DiscreetYellow);
FillRect(BRect(0, 0, 20, 20));

//Draw Text
BFont mFont;
int32 stringWidth;
GetFont(&mFont);
mFont.SetSize(40);
stringWidth = mFont.StringWidth(STR_APP_NAME);

SetHighColor(Black);
SetLowColor(DiscreetLightGray);
SetFontSize(40);
MovePenTo((Bounds().right / 2) - (stringWidth / 2), 70);
DrawString(STR_APP_NAME);

SetHighColor(Black);
SetLowColor(DiscreetLightGray);
SetFontSize(12);
MovePenTo(5, Bounds().bottom - 60);
tempString.SetTo(STR_BY[INT_LANGUAGE]);
tempString << " " << STR_AUTHOR;
DrawString(tempString.String());

MovePenTo(5, Bounds().bottom - 46);
tempString.SetTo(STR_ALSO_KNOWN_AS[INT_LANGUAGE]);
tempString << ": " << STR_AUTHOR_NICK;
DrawString(tempString.String());

MovePenTo(5, Bounds().bottom - 32);
DrawString(STR_AUTHOR_EMAIL);

MovePenTo(5, Bounds().bottom - 18);
tempString.SetTo(STR_VERSION_NUMBER[INT_LANGUAGE]);
tempString << ": " << STR_VERSIONNUMBER;
DrawString(tempString.String());

MovePenTo(5, Bounds().bottom - 4);
tempString.SetTo(STR_BUILD_NUMBER[INT_LANGUAGE]);
tempString << ": " << BUILD_NUMBER;
DrawString(tempString.String());
}

//---------------------------------------------------------------
void AboutView::MouseDown(BPoint point)
{
/*
	if (point.x < 7 && point.x > 1 && point.y < 7 && point.y > 1)
	{
	be_app->PostMessage(MSG_OPEN_GL_GAME);
	}
*/
}

