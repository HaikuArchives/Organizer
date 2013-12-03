// Standard Includes -----------------------------------------------------------

// System Includes -------------------------------------------------------------
#include "mWindow.h"

// Project Includes ------------------------------------------------------------

// Local Includes --------------------------------------------------------------

// Local Defines ---------------------------------------------------------------

// Globals Defines -------------------------------------------------------------

//---------------------------------------------------------------
mWindow::mWindow()
			 : BWindow(BRect(100, 100, 900, 900), "fishingSubmarine Organizer", B_TITLED_WINDOW, 0)
{
//Set the correct window rect
MSave savefile("savefile");
SetSettingsPath(&fPath);
tmpRect.Set(Bounds().left, Bounds().top, Bounds().right, Bounds().bottom);
savefile.FindRect(fPath, SAVE_FILE_NAME, SAVE_WINDOW_RECT, &tmpRect, tmpRect);
MoveTo(tmpRect.left, tmpRect.top);
ResizeTo(tmpRect.right - tmpRect.left, tmpRect.bottom - tmpRect.top);

_MenuView = new MenuView(BRect(0, 0, 1600, 20),"_MenuView", B_FOLLOW_TOP | B_FOLLOW_LEFT | B_FOLLOW_RIGHT, B_WILL_DRAW);
_CalenderView = new CalenderView(BRect(0, 50, 420, 430), "_CalenderView", B_FOLLOW_TOP | B_FOLLOW_LEFT, B_WILL_DRAW);
_NavigateDateView = new NavigateDateView(BRect(0, 10, 420, 50), "_NavigateDateView", B_FOLLOW_TOP | B_FOLLOW_LEFT, B_WILL_DRAW,
						 _CalenderView->mCalender->Year(), _CalenderView->mCalender->Month());
_NoteListView = new NoteListView(BRect(420, 0, 420 + 160, 430), "_NoteListView", B_FOLLOW_TOP | B_FOLLOW_LEFT, B_WILL_DRAW);

AddChild(_MenuView);
AddChild(_CalenderView);
AddChild(_NavigateDateView);
AddChild(_NoteListView);

//Add preferences
fLanguage = 0;
fTheme = 1;
ApplyTheme();


}

//---------------------------------------------------------------
mWindow::~mWindow()
{

}

//---------------------------------------------------------------
void mWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	case MSG_QUIT:
		SaveQuitSettings();
		be_app->PostMessage(B_QUIT_REQUESTED);
	break;
	case MSG_ADD_APOINTMENT:
	//Add
	break;
	case MSG_ADD_SCRIPT:
	//Add
	break;
	case MSG_ADD_NOTE:
	//Add
	break;
	case MSG_CHANGE_MONTH:
		for (int a = 0; a < 12; a++)
		{
			if (_NavigateDateView->mMenuMonth->ItemAt(a)->IsMarked())
			{
			_CalenderView->mCalender->SetMonth(a + 1);
			}
		}
	break;
	case MSG_CHANGE_YEAR:
		for (int a = 0; a < 15; a++)
		{
			if (_NavigateDateView->mMenuYear->ItemAt(a)->IsMarked())
			{
			tmpString.SetTo(_NavigateDateView->mMenuYear->ItemAt(a)->Label());
			}
		}
	_CalenderView->mCalender->SetYear(atoi(tmpString.String()));
	break;
	case MSG_ABOUT:
	be_app->PostMessage(message);
	break;
	case MSG_PREFERENCES:
	be_app->PostMessage(message);
	break;
	case MSG_CALENDER:
	{
	message->FindString("button", &fMouseButtonClicked);
	message->FindString("day", &tmpString);
	fDayOfMouseClick = atoi(tmpString.String());
	message->FindString("month", &tmpString);
	fMonthOfMouseClick = atoi(tmpString.String());
	message->FindString("year", &tmpString);
	fYearOfMouseClick = atoi(tmpString.String());
		//If primary mouseclick
		if (!strcmp(fMouseButtonClicked.String(), "PrimaryMouseButton"))
		{
			//Add
		}
		
		//If secondary mouseclick
		if (!strcmp(fMouseButtonClicked.String(), "SecondaryMouseButton"))
		{
			RightClickMenu(fDayOfMouseClick, fMonthOfMouseClick, fYearOfMouseClick);
		}
	break;
	}
	default:
	BWindow::MessageReceived(message);
	}
}

//---------------------------------------------------------------
bool mWindow::QuitRequested()
{
	SaveQuitSettings();
	be_app->PostMessage(B_QUIT_REQUESTED);
	return BWindow::QuitRequested();
}

//---------------------------------------------------------------
void mWindow::RightClickMenu(int32 mDayOfMouseClick, int32 mMonthOfMouseClick, 
								int32 mYearOfMouseClick)
{
BPoint fMousePosition;
uint32 location;

//Get mouse position
_MenuView->GetMouse(&fMousePosition, &location, false);
fMousePosition.Set(fMousePosition.x + Frame().left, fMousePosition.y + Frame().top);

//The popupmenu
mRCPopUpMenu = new BPopUpMenu("mRCPopUpMenu", true, false, B_ITEMS_IN_COLUMN);

//Add items here
//Note
mRCMenuItem = new BMenuItem(STR_ADD_NOTE[fLanguage], new BMessage(MSG_ADD_NOTE));
mRCPopUpMenu->AddItem(mRCMenuItem);
//Apointment
mRCMenuItem = new BMenuItem(STR_ADD_APOINTMENT[fLanguage], new BMessage(MSG_ADD_APOINTMENT));
mRCPopUpMenu->AddItem(mRCMenuItem);
//Script
mRCMenuItem = new BMenuItem(STR_ADD_SCRIPT[fLanguage], new BMessage(MSG_ADD_SCRIPT));
mRCPopUpMenu->AddItem(mRCMenuItem);

//PostMessage
mRCPopUpMenu->Go(fMousePosition);
	if(mRCMenuItem != NULL)
	{
	PostMessage(mRCMenuItem->Message());
	}
}

//---------------------------------------------------------------
void mWindow::ApplyTheme()
{
	switch (fTheme)
	{
	//DefaultGray
	case 1:
	_MenuView->SetViewColor(BeBackgroundGrey);
	_CalenderView->SetViewColor(BeBackgroundGrey);
	_CalenderView->mCalender->SetBackgroundColor(BeBackgroundGrey);
	_NavigateDateView->SetViewColor(BeBackgroundGrey);
	break;
	//PineApple
	case 2:
	_MenuView->SetViewColor(PineAppleDarkGreen);
	_CalenderView->SetViewColor(PineAppleYellow);
	_CalenderView->mCalender->SetBackgroundColor(PineAppleYellow);
	_NavigateDateView->SetViewColor(PineAppleGreen);
	//Add
	break;
	case 3:
	
	break;
	}
}

//---------------------------------------------------------------
void mWindow::SaveQuitSettings()
{
tmpRect = Frame();
MSave savefile("savefile");
//Set the correct folder
SetSettingsPath(&fPath);
//Save
savefile.AddRect(fPath, SAVE_FILE_NAME, SAVE_WINDOW_RECT, tmpRect, true);
}

//---------------------------------------------------------------
void mWindow::SetSettingsPath(BPath *path)
{
BPath Path;
BString string;
find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
string.SetTo(Path.Path());
string.Append(SAVE_SETTINGS_PATH);
path->SetTo(string.String());
}
