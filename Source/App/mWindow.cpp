// Standard Includes -----------------------------------------------------------

// System Includes -------------------------------------------------------------
#include "mWindow.h"

// Project Includes ------------------------------------------------------------

// Local Includes --------------------------------------------------------------

// Local Defines ---------------------------------------------------------------

// Globals Defines -------------------------------------------------------------

//---------------------------------------------------------------
mWindow::mWindow()
			 : BWindow(BRect(100, 100, 700, 530), "fishingSubmarine Organizer", B_TITLED_WINDOW, 0)
{
//Set the correct window rect
MSave savefile("savefile");
GetSettingsPath(&fPath);

tmpRect.Set(Frame().left, Frame().top, Frame().right, Frame().bottom);
savefile.FindRect(fPath, SAVE_FILE_NAME, SAVE_WINDOW_RECT, &tmpRect, tmpRect);
MoveTo(tmpRect.left, tmpRect.top);
ResizeTo(tmpRect.right - tmpRect.left, tmpRect.bottom - tmpRect.top);
SetSizeLimits(600, 1600, 430, 1200);

//Add preferences
INT_THEME = 1;

_MenuView = new MenuView(BRect(0, 0, 1600, 20),"_MenuView", B_FOLLOW_TOP | B_FOLLOW_LEFT | B_FOLLOW_RIGHT, B_WILL_DRAW);
_CalenderView = new CalenderView(BRect(0, 50, 420, Bounds().bottom), "_CalenderView", B_FOLLOW_TOP_BOTTOM | B_FOLLOW_LEFT, B_WILL_DRAW | B_NAVIGABLE);
INT_YEAR = _CalenderView->mCalender->Year();
INT_MONTH = _CalenderView->mCalender->Month();
_NavigateDateView = new NavigateDateView(BRect(0, 10, 420, 50), "_NavigateDateView", B_FOLLOW_TOP | B_FOLLOW_LEFT, B_WILL_DRAW | B_NAVIGABLE);
_NoteListView = new NoteListView(BRect(420, 0, Bounds().right, Bounds().bottom), "_NoteListView", B_FOLLOW_ALL, B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS);

AddChild(_MenuView);
AddChild(_CalenderView);
AddChild(_NavigateDateView);
AddChild(_NoteListView);
ApplyTheme();

//_NoteListView->AddItem(new BStringItem("name", 1), false);
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
	//Fix this!
	case MSG_EDIT_SOMETHING:
	{
			BString PathToSelectedFile;	
			GetPathToSelectedFile(&PathToSelectedFile);
			
			if (!strcmp(TypeInFile(PathToSelectedFile.String()).String(), "Note"))
			{
			BMessage * Message = new BMessage(MSG_EDIT_NOTE_WIN);
			Message->AddString(SAVE_FILE_TYPE, TypeInFile(PathToSelectedFile.String()).String());
			Message->AddString(SAVE_FILE_TITLE, TitleInFile(PathToSelectedFile.String()).String());
			Message->AddString(SAVE_FILE_PATH, PathToSelectedFile);
			Message->AddString(SAVE_FILE_TIME, TimeInFile(PathToSelectedFile.String()).String());
			Message->AddString(SAVE_FILE_NOTE, NoteInFile(PathToSelectedFile.String()).String());
			Message->AddString(SAVE_FILE_NOTIFY, NotifyInFile(PathToSelectedFile.String()).String());
			
			be_app->PostMessage(Message);
			}
			else
			{
				if (!strcmp(TypeInFile(PathToSelectedFile.String()).String(), "Script"))
				{
				BMessage * Message = new BMessage(MSG_EDIT_SCRIPT_WIN);
				
				Message->AddString(SAVE_FILE_TYPE, TypeInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_TITLE, TitleInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_PATH, PathToSelectedFile);
				Message->AddString(SAVE_FILE_TIME, TimeInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_NOTE, NoteInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_NOTIFY, NotifyInFile(PathToSelectedFile.String()).String());
				
				be_app->PostMessage(Message);
				}
				else
				{
				//Its an apointment
				BMessage * Message = new BMessage(MSG_EDIT_APOINTMENT_WIN);
				
				Message->AddString(SAVE_FILE_TYPE, TypeInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_TITLE, TitleInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_PATH, PathToSelectedFile);
				Message->AddString(SAVE_FILE_TIME, TimeInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_NOTE, NoteInFile(PathToSelectedFile.String()).String());
				Message->AddString(SAVE_FILE_NOTIFY, NotifyInFile(PathToSelectedFile.String()).String());
			
				be_app->PostMessage(Message);
				}
			}
	break;
	}
	case MSG_QUIT:
		SaveQuitSettings();
		be_app->PostMessage(B_QUIT_REQUESTED);
	break;
	case MSG_CHANGE_MONTH:
		for (int a = 0; a < 12; a++)
		{
			if (_NavigateDateView->mMenuMonth->ItemAt(a)->IsMarked())
			{
			_CalenderView->mCalender->SetMonth(a + 1);
			}
		}
		
	//Get notes
	GetNotes();
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
	
	//Get notes
	GetNotes();
	break;
	case MSG_ADD_SOMETHING:
	{
	BAlert * mAlert = new BAlert("Add What", STR_ADD_WHAT[INT_LANGUAGE], STR_APOINTMENT[INT_LANGUAGE], STR_SCRIPT[INT_LANGUAGE], STR_NOTE[INT_LANGUAGE]);
		switch (mAlert->Go())
		{
		case 2:
		PostMessage(MSG_ADD_NOTE);
		break;
		case 1:
		PostMessage(MSG_ADD_SCRIPT);
		break;
		case 0:
		PostMessage(MSG_ADD_APOINTMENT);
		break;
		}
	break;
	}
	case MSG_REMOVE_SOMETHING:
		GetPathToSelectedFile(&tmpString4);
		tmpString4.Prepend("rm -f ");
		system(tmpString4.String());
		_NoteListView->mNoteListView->RemoveItem(_NoteListView->mNoteListView->CurrentSelection());
			if (_NoteListView->mNoteListView->CountItems() == 0)
			{
			_NoteListView->mEditButton->SetEnabled(false);
			_NoteListView->mRemoveButton->SetEnabled(false);
			}
			else
			{
			_NoteListView->mEditButton->SetEnabled(true);
			_NoteListView->mRemoveButton->SetEnabled(true);
			_NoteListView->mNoteListView->Select(0);
			}
	break;
	case MSG_NEW_ITEM_SELECTED:
		
	break;
	case MSG_ADD_NOTE:
	{
		BMessage * Message = new BMessage(MSG_ADD_NOTE_WIN);
		Message->AddInt32("Year", _CalenderView->mCalender->Year());
		Message->AddInt32("Month", _CalenderView->mCalender->Month());
		Message->AddInt32("Day", _CalenderView->mCalender->Day());
		be_app->PostMessage(Message);
	break;
	}
	case MSG_ADD_SCRIPT:
	{
		BMessage * Message = new BMessage(MSG_ADD_SCRIPT_WIN);
		Message->AddInt32("Year", _CalenderView->mCalender->Year());
		Message->AddInt32("Month", _CalenderView->mCalender->Month());
		Message->AddInt32("Day", _CalenderView->mCalender->Day());
		be_app->PostMessage(Message);
	break;
	}
	case MSG_ADD_APOINTMENT:
	{
		BMessage * Message = new BMessage(MSG_ADD_APOINTMENT_WIN);
		Message->AddInt32("Year", _CalenderView->mCalender->Year());
		Message->AddInt32("Month", _CalenderView->mCalender->Month());
		Message->AddInt32("Day", _CalenderView->mCalender->Day());
		be_app->PostMessage(Message);
	break;
	}
	case MSG_ABOUT:
	be_app->PostMessage(message);
	break;
	case MSG_EXPORT_HTML:
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
	INT_YEAR = _CalenderView->mCalender->Year();
	INT_MONTH = _CalenderView->mCalender->Month();
	INT_DAY = _CalenderView->mCalender->Day();
	
	//Get notes
	GetNotes();
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
	be_app->PostMessage(MSG_QUIT_PLEASE);
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(1);
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
mRCMenuItem = new BMenuItem(STR_ADD_NOTE[INT_LANGUAGE], new BMessage(MSG_ADD_NOTE));
mRCPopUpMenu->AddItem(mRCMenuItem);
//Apointment
mRCMenuItem = new BMenuItem(STR_ADD_APOINTMENT[INT_LANGUAGE], new BMessage(MSG_ADD_APOINTMENT));
mRCPopUpMenu->AddItem(mRCMenuItem);
//Script
mRCMenuItem = new BMenuItem(STR_ADD_SCRIPT[INT_LANGUAGE], new BMessage(MSG_ADD_SCRIPT));
mRCPopUpMenu->AddItem(mRCMenuItem);

//PostMessage
mRCPopUpMenu->Go(fMousePosition, true);
	if(mRCMenuItem != NULL)
	{
		if (mRCPopUpMenu->ItemAt(0)->IsMarked() || mRCPopUpMenu->ItemAt(1)->IsMarked() || mRCPopUpMenu->ItemAt(2)->IsMarked())
		{
			if (!strcmp(mRCPopUpMenu->ItemAt(mRCPopUpMenu->IndexOf(mRCPopUpMenu->FindMarked()))->Label(), STR_ADD_NOTE[INT_LANGUAGE]))
			{
			PostMessage(MSG_ADD_NOTE);
			}
			if (!strcmp(mRCPopUpMenu->ItemAt(mRCPopUpMenu->IndexOf(mRCPopUpMenu->FindMarked()))->Label(), STR_ADD_APOINTMENT[INT_LANGUAGE]))
			{
			PostMessage(MSG_ADD_APOINTMENT);
			}
			if (!strcmp(mRCPopUpMenu->ItemAt(mRCPopUpMenu->IndexOf(mRCPopUpMenu->FindMarked()))->Label(), STR_ADD_SCRIPT[INT_LANGUAGE]))
			{
			PostMessage(MSG_ADD_SCRIPT);
			}
		}
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
GetSettingsPath(&fPath);

//Save
savefile.AddRect(fPath, SAVE_FILE_NAME, SAVE_WINDOW_RECT, tmpRect, true);
}

//---------------------------------------------------------------
void mWindow::GetSettingsPath(BPath *path)
{
BPath Path;
BString string;
find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
string.SetTo(Path.Path());
string.Append(SAVE_SETTINGS_PATH);
path->SetTo(string.String());
}

//---------------------------------------------------------------
void mWindow::GetNotes()
{
_NoteListView->mNoteListView->RemoveItems(0, 100);
MSave Save("save");
BPath fPath;
BString tempString;
BString tempString2;
BString tempString3;
BString tempString4;
BString FilePath;
BEntry Entry("/boot/home");

find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &fPath);
tempString.SetTo(fPath.Path());
tempString.Append(SAVE_NOTE_PATH);
fPath = tempString.String();
tempString.SetTo("");
tempString <<_CalenderView->mCalender->Day() << "-" << _CalenderView->mCalender->Month() << _CalenderView->mCalender->Year();
	for (int a = 1; a <= INT_MAXFILES; a++)
	{
	tempString2.SetTo(tempString.String());
	tempString2 << "-" << a;
	
	FilePath.SetTo(fPath.Path());
	FilePath << tempString2.String();
	
	Entry.SetTo(FilePath.String());

		if (Entry.Exists())
		{
		//The file is there!!!
		Save.FindString(fPath, tempString2.String(), SAVE_FILE_TITLE, &tempString3, "M_ERROR");
		Save.FindString(fPath, tempString2.String(), SAVE_FILE_TYPE, &tempString4, "M_ERROR");
			if (!strcmp(tempString4.String(), "Note"))
			{
			_NoteListView->mNoteListView->AddItem(new MCustomListItem(tempString3.String(), STR_NOTE[INT_LANGUAGE]));
			}
			else
			{
				if (!strcmp(tempString4.String(), "Apointment"))
				{
				_NoteListView->mNoteListView->AddItem(new MCustomListItem(tempString3.String(), STR_APOINTMENT[INT_LANGUAGE]));
				}
				else
				{
				_NoteListView->mNoteListView->AddItem(new MCustomListItem(tempString3.String(), STR_SCRIPT[INT_LANGUAGE]));
				}
			}
		//Done
		}
	}
	if (_NoteListView->mNoteListView->CountItems() == 0)
	{
	_NoteListView->mEditButton->SetEnabled(false);
	_NoteListView->mRemoveButton->SetEnabled(false);
	}
	else
	{
	_NoteListView->mEditButton->SetEnabled(true);
	_NoteListView->mRemoveButton->SetEnabled(true);
	_NoteListView->mNoteListView->Select(0);
	}
}

//---------------------------------------------------------------
void mWindow::GetPathToSelectedFile(BString* string)
{
int selectedItemNumber;
BString PathWithoutNumber;
BString FullPath;
BString FilePath;
BString FileContent;
selectedItemNumber = 0;

GetSettingsPath(&fPath);
PathWithoutNumber.SetTo(fPath.Path());
PathWithoutNumber.RemoveLast(SAVE_PATH_PART_3_1);
PathWithoutNumber.Append(SAVE_PATH_PART_3_2);
PathWithoutNumber << "/" <<_CalenderView->mCalender->Day() << "-" << _CalenderView->mCalender->Month() << _CalenderView->mCalender->Year();
	for (int a = 1; a <= INT_MAXFILES; a++)
	{
	FullPath.SetTo(PathWithoutNumber.String());
	FullPath << "-" << a;

	BEntry Entry(FullPath.String());
	
		if (Entry.Exists())
		{
			if (selectedItemNumber == _NoteListView->mNoteListView->CurrentSelection())
			{
			*string = FullPath.String();
			}
		selectedItemNumber++;
		}
	}
}

//---------------------------------------------------------------
BString mWindow::TypeInFile(const char* path)
{
BString tempString;
MSave Save("save");

Save.FindString(path, SAVE_FILE_TYPE, &tempString, "M_ERROR");

return (tempString);
}

//---------------------------------------------------------------
BString mWindow::TimeInFile(const char* path)
{
BString tempString;
MSave Save("save");

Save.FindString(path, SAVE_FILE_TIME, &tempString, "M_ERROR");

return (tempString);
}

//---------------------------------------------------------------
BString mWindow::NoteInFile(const char* path)
{
BString tempString;
MSave Save("save");

Save.FindString(path, SAVE_FILE_NOTE, &tempString, "M_ERROR");

return (tempString);
}

//---------------------------------------------------------------
BString mWindow::TitleInFile(const char* path)
{
BString tempString;
MSave Save("save");

Save.FindString(path, SAVE_FILE_TITLE, &tempString, "M_ERROR");

return (tempString);
}

//---------------------------------------------------------------
BString mWindow::NotifyInFile(const char* path)
{
BString tempString;
MSave Save("save");

Save.FindString(path, SAVE_FILE_NOTIFY, &tempString, "M_ERROR");

return (tempString);
}


