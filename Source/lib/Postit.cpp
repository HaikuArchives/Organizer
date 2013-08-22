// Standard Includes -----------------------------------------------------------

// System Includes -------------------------------------------------------------
#include "Postit.h"

// Project Includes ------------------------------------------------------------

// Local Includes --------------------------------------------------------------

// Local Defines ---------------------------------------------------------------
const rgb_color PostItsYellow = 	{244, 204, 66};

const BRect ButtonFrame1			(45, 10, 120, 30);
const BRect ButtonFrame2			(130, 10, 205, 30);
const BRect ButtonFrame3			(215, 10, 290, 30);
const BRect ButtonViewFrame			(1, 260, 299, 299);

// Globals ---------------------------------------------------------------------

//Class
//-----------------------------------------------------------------
MPostit::MPostit(const char* name, 
				const char* text, 
				const char* button1_text,
				const char* button2_text = NULL, 
				const char* button3_text = NULL)
				: BWindow(BRect(100, 100, 200, 200), text, B_NO_BORDER_WINDOW_LOOK,
							B_NORMAL_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_MOVABLE, B_ALL_WORKSPACES)
{
Post_Name.SetTo(name);
Post_Text.SetTo(text);
Button1_Text.SetTo(button1_text);
	if (button2_text != NULL)
	{
	Button2_Text.SetTo(button2_text);
	fButton2Enabled = true;
		if (button3_text != NULL)
		{
		Button3_Text.SetTo(button3_text);
		fButton3Enabled = true;
		}
		else
		{
		fButton3Enabled = false;
		}
	}
	else
	{
	fButton2Enabled = false;
	fButton3Enabled = false;
	}
	
//Set it up
fWindowWidth = 300;
fWindowHeight = 300;
_CenterWindow(fWindowWidth, fWindowHeight);

//Add the textview
PostTextView = new BTextView(BRect(Bounds().left + 1, Bounds().top + 1, Bounds().right - 1,
							Bounds().bottom - 40), "", BRect(10, 10, fWindowWidth - 20, fWindowHeight - 20),
							B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
AddChild(PostTextView);
//Config the textview
PostTextView->SetViewColor(PostItsYellow);
PostTextView->SetText(Post_Text.String());
PostTextView->MakeEditable(false);
PostTextView->MakeSelectable(false);
BFont font;
font.SetSize(13);
PostTextView->SetFontAndColor(&font);

//Add the buttonview
ButtonView = new BView(ButtonViewFrame, "ButtonView", B_FOLLOW_BOTTOM | B_FOLLOW_LEFT, B_WILL_DRAW);
ButtonView->SetViewColor(PostItsYellow);
AddChild(ButtonView);

//Add the buttons
	//1
	if (fButton2Enabled)
	{
	TempFrame.Set(ButtonFrame2.left, ButtonFrame2.top, ButtonFrame2.right, ButtonFrame2.bottom);
	}
	else
	{
	TempFrame.Set(ButtonFrame3.left, ButtonFrame3.top, ButtonFrame3.right, ButtonFrame3.bottom);
	}
	if (fButton3Enabled)
	{
	TempFrame.Set(ButtonFrame1.left, ButtonFrame1.top, ButtonFrame1.right, ButtonFrame1.bottom);
	}
PostButton1 = new BButton(TempFrame, "PostButton1", Button1_Text.String(), new BMessage(MSG_BUTTON1));
PostButton1->MakeDefault(true);
ButtonView->AddChild(PostButton1);
	//2
	if (fButton2Enabled)
	{
		if (fButton3Enabled)
		{
		TempFrame.Set(ButtonFrame2.left, ButtonFrame2.top, ButtonFrame2.right, ButtonFrame2.bottom);
		}
		else
		{
		TempFrame.Set(ButtonFrame3.left, ButtonFrame3.top, ButtonFrame3.right, ButtonFrame3.bottom);
		}
	PostButton2 = new BButton(TempFrame, "PostButton2", Button2_Text.String(), new BMessage(MSG_BUTTON2));
	PostButton2->MakeDefault(true);
	ButtonView->AddChild(PostButton2);
	}
	//3
	if (fButton3Enabled)
	{
	TempFrame.Set(ButtonFrame3.left, ButtonFrame3.top, ButtonFrame3.right, ButtonFrame3.bottom);
	PostButton3 = new BButton(TempFrame, "PostButton3", Button3_Text.String(), new BMessage(MSG_BUTTON3));
	PostButton3->MakeDefault(true);
	ButtonView->AddChild(PostButton3);
	}

	//Make sure the window is big enough
	if (PostTextView->CountLines() >= 14)
	{
	ResizeTo(fWindowWidth, (PostTextView->CountLines() * 17) + 60);
	}
}

//-----------------------------------------------------------------
MPostit::~MPostit()
{

}

//-----------------------------------------------------------------
void MPostit::MessageReceived(BMessage *message)
{
	switch (message->what)
	{
	case MSG_BUTTON1:
		Return(Button1_Text.String());
		Close();
	break;
	case MSG_BUTTON2:
		Return(Button2_Text.String());
		Close();
	break;
	case MSG_BUTTON3:
		Return(Button3_Text.String());
		Close();
	break;
	default:
	
	break;
	}
}

//-----------------------------------------------------------------
const char* MPostit::Return(const char* return_text)
{
return return_text;
}

//-----------------------------------------------------------------
void MPostit::Go()
{
Show();
}

//-----------------------------------------------------------------
void MPostit::_CenterWindow(int window_width, int window_height)
{
BRect screenBounds;
BScreen screen(B_MAIN_SCREEN_ID);
screenBounds.Set(screen.Frame().left, screen.Frame().top, screen.Frame().right, screen.Frame().bottom);
MoveTo((screenBounds.right / 2) - (window_width / 2), (screenBounds.bottom / 4));
ResizeTo(fWindowWidth, fWindowHeight);
}
