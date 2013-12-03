// Standard Includes -----------------------------------------------------------

// System Includes -------------------------------------------------------------
#include "Alert.h"

// Project Includes ------------------------------------------------------------

// Local Includes --------------------------------------------------------------

// Local Defines ---------------------------------------------------------------
const BRect ButtonAlertFrame1		(235, 60, 310, 90);
const BRect ButtonAlertFrame2		(235, 60, 310, 90);
const BRect ButtonAlertFrame3		(235, 60, 310, 90);

// Globals ---------------------------------------------------------------------

//Class
//-----------------------------------------------------------------
MAlert::MAlert(const char* name, 
				const char* text, 
				const char* button1_text,
				const char* button2_text = NULL, 
				const char* button3_text = NULL, 
				bool post_its_look = false,
				icon_type icon = M_INFO)
				: BWindow(BRect(100, 100, 200, 200), text, B_NO_BORDER_WINDOW_LOOK,
							B_NORMAL_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_MOVABLE, B_ALL_WORKSPACES)
{
fIconNumber = icon;
fPostItsLook = post_its_look;
Alert_Name.SetTo(name);
Alert_Text.SetTo(text);
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
	}
	

_SetupEverything();	
std::cout << "Setup everything" << std::endl;
}

//-----------------------------------------------------------------
MAlert::~MAlert()
{

}

//-----------------------------------------------------------------
void MAlert::Go()
{
Show();
}

//-----------------------------------------------------------------
void MAlert::SetText(const char* text)
{
Alert_Text.SetTo(text);
AlertTextView->SetText(Alert_Text.String());
}

//-----------------------------------------------------------------
const char* MAlert::Text()
{
return AlertTextView->Text();
}

//-----------------------------------------------------------------
void MAlert::_CenterWindow(int window_width, int window_height)
{
BRect screenBounds;
BScreen screen(B_MAIN_SCREEN_ID);
screenBounds.Set(screen.Frame().left, screen.Frame().top, screen.Frame().right, screen.Frame().bottom);
MoveTo((screenBounds.right / 2) - (window_width / 2), (screenBounds.bottom / 4));
ResizeTo(fWindowWidth, fWindowHeight);
}

//-----------------------------------------------------------------
void MAlert::_SetupEverything()
{
SetTitle(Alert_Name.String());
	//CrossRoad
	if (fPostItsLook)
	{
	fWindowWidth = 300;
	fWindowHeight = 300;
	_CenterWindow(fWindowWidth, fWindowHeight);
	
	//Add the textview
	AlertTextView = new BTextView(BRect(Bounds().left + 1, Bounds().top + 1, Bounds().right - 1,
								Bounds().bottom - 40), "", BRect(10, 10, fWindowWidth - 20, fWindowHeight - 20),
								B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	AddChild(AlertTextView);
	//Config the textview
	AlertTextView->SetViewColor(PostItsYellow);
	AlertTextView->SetText(Alert_Text.String());
	AlertTextView->MakeEditable(false);
	AlertTextView->MakeSelectable(false);
	
	//Add the buttonview
	ButtonView = new BView();
	AddChild(ButtonView);
	
	//Add the buttons
	//1
		if (fButton2Enabled)
		{
		TempFrame.Set(ButtonPostItsFrame2.left, ButtonPostItsFrame2.top, ButtonPostItsFrame2.right, ButtonPostItsFrame2.bottom);
		}
		else
		{
		std::cout << "only one button" << std::endl;
		TempFrame.Set(ButtonPostItsFrame3.left, ButtonPostItsFrame3.top, ButtonPostItsFrame3.right, ButtonPostItsFrame3.bottom);
		}
		if (fButton3Enabled)
		{
		TempFrame.Set(ButtonPostItsFrame1.left, ButtonPostItsFrame1.top, ButtonPostItsFrame1.right, ButtonPostItsFrame1.bottom);
		}
	AlertButton1 = new BButton(TempFrame, "AlertButton1", Button1_Text.String(), new BMessage(MSG_BUTTON1));
	AlertButton1->MakeDefault(true);
	ButtonView->AddChild(AlertButton1);
	//2
		if (fButton2Enabled)
		{
			if (fButton3Enabled)
			{
			TempFrame.Set(ButtonPostItsFrame2.left, ButtonPostItsFrame2.top, ButtonPostItsFrame2.right, ButtonPostItsFrame2.bottom);
			}
			else
			{
			std::cout << "Only two buttons" << std::endl;
			TempFrame.Set(ButtonPostItsFrame3.left, ButtonPostItsFrame3.top, ButtonPostItsFrame3.right, ButtonPostItsFrame3.bottom);
			}
		AlertButton2 = new BButton(TempFrame, "AlertButton2", Button2_Text.String(), new BMessage(MSG_BUTTON2));
		AlertButton2->MakeDefault(true);
		ButtonView->AddChild(AlertButton2);
		}
	//3
		if (fButton3Enabled)
		{
		std::cout << "OMG, three buttons" << std::endl;
		TempFrame.Set(ButtonPostItsFrame3.left, ButtonPostItsFrame3.top, ButtonPostItsFrame3.right, ButtonPostItsFrame3.bottom);
		AlertButton3 = new BButton(TempFrame, "AlertButton3", Button3_Text.String(), new BMessage(MSG_BUTTON3));
		AlertButton3->MakeDefault(true);
		ButtonView->AddChild(AlertButton3);
		}
	}
	//It is not PostItsLook
	else
	{
	fWindowWidth = 320;
	//100 as default height
	fWindowHeight = 100;
	_CenterWindow(fWindowWidth, fWindowHeight);
	
	AlertTextView = new BTextView(BRect(Bounds().left + 40, Bounds().top + 1, Bounds().right - 1,
								Bounds().bottom - 40), "", BRect(10, 10, fWindowWidth - 20, fWindowHeight - 20),
								B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	AddChild(AlertTextView);
	}


}


