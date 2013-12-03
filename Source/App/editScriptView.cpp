//-----------------------  Local includes  ----------------------
#include "editScriptView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

//---------------------------------------------------------------
EditScriptView::EditScriptView(BRect frame, const char *name, uint32 resizeMask, uint32 flags, const char* title, const char* time, const char* note, bool notify)
		: BView(frame, name, resizeMask, flags)
{
//Set it up
SetViewColor(BeBack);

//Construct
mTitleControl = new BTextControl(BRect(5, 5, 210, 35), "mTitleControl", STR_SCRIPT_NAME[INT_LANGUAGE], "MyScript",
					 new BMessage(MSG_BOGUS), B_FOLLOW_LEFT | B_FOLLOW_TOP);
mTitleControl->SetDivider(90);
mTitleControl->SetText(title);

mHourMenu = new BMenu("mHourMenu");
mHourMenu->SetLabelFromMarked(true);

mMinuteMenu = new BMenu("mMinuteMenu");
mMinuteMenu->SetLabelFromMarked(true); 

mHistoryMenu = new BMenu("mHistoryMenu");
mHistoryMenu->SetLabelFromMarked(true); 

mHourMenuField = new BMenuField(BRect(220, 5, 370, 25), "mHourMenuField",  STR_RUN_SCRIPT_AT[INT_LANGUAGE],
					mHourMenu,  B_FOLLOW_LEFT | B_FOLLOW_TOP);
mHourMenuField->SetDivider(110);

mMinuteMenuField = new BMenuField(BRect(362, 5, 410, 25), "mMinuteMenuField", ":",
					mMinuteMenu,  B_FOLLOW_LEFT | B_FOLLOW_TOP);
mMinuteMenuField->SetDivider(5);

mTextView = new BTextView(BRect(5, 50, frame.right - (10 + B_V_SCROLL_BAR_WIDTH), frame.bottom - (43 + B_H_SCROLL_BAR_HEIGHT)),
				 "mScriptTextView", BRect(2, 2, frame.right * 3, frame.bottom - 45), B_FOLLOW_ALL_SIDES);
AddChild(mScriptScrollView = new BScrollView("mScriptScrollBar", mTextView, B_FOLLOW_ALL_SIDES, 0, true, true));
mTextView->SetWordWrap(false);
mTextView->SetText(note);
mTextView->MakeEditable(true);
mTextView->MakeSelectable(true);
mTextView->ForceFontAliasing(true);

mRunScriptBox = new BCheckBox(BRect(260, 30, 330, 45), "mRunScriptBox", STR_RUN_SCRIPT[INT_LANGUAGE], new BMessage(MSG_RUN_SCRIPT_CHECKBOX));
mRunScriptBox->SetValue(notify);

mSaveButton = new BButton(BRect(frame.right - 120, frame.bottom - 30, frame.right - 20, frame.bottom - 10), "mSaveButton", STR_SAVE[INT_LANGUAGE], new BMessage(MSG_SAVE_SCRIPT));
mCancelButton = new BButton(BRect(frame.right - 230, frame.bottom - 30, frame.right - 130, frame.bottom - 10), "mCancelButton", STR_CANCEL[INT_LANGUAGE], new BMessage(MSG_CANCEL));

mHistoryMenuField = new BMenuField(BRect(10, frame.bottom - 30, 160, frame.bottom - 15), "mHistoryMenuField", STR_HISTORY[INT_LANGUAGE],
					mHistoryMenu,  B_FOLLOW_LEFT | B_FOLLOW_TOP);
mHistoryMenuField->SetDivider(50);

//Set up and add
tmpString2.SetTo(time);
tmpString2.Remove((tmpString2.FindFirst(":")), tmpString2.CountChars() - (tmpString2.FindFirst(":")));
	for (int a = 0; a <= 23; a++)
	{
	tmpString.SetTo("");
	tmpString << a;
	mHourMenu->AddItem(mMenuItem = new BMenuItem(tmpString.String(), new BMessage(MSG_BOGUS)));
		if (a == atoi(tmpString2.String()))
		{
		mMenuItem->SetMarked(true);
		}
	}
	
tmpString3.SetTo(time);
tmpString3.Remove(0, tmpString2.CountChars() + 1);
	for (int a = 0; a < 60; a++)
	{
	tmpString.SetTo("");
	tmpString << a;
	mMinuteMenu->AddItem(mMenuItem = new BMenuItem(tmpString.String(), new BMessage(MSG_BOGUS)));
		if (a == atoi(tmpString3.String()))
		{
		mMenuItem->SetMarked(true);
		}
	}
	
	
AddChild(mTitleControl);
AddChild(mHourMenuField);
AddChild(mMinuteMenuField);
AddChild(mRunScriptBox);
AddChild(mSaveButton);
AddChild(mCancelButton);
AddChild(mHistoryMenuField);

CheckNotify();
History();
}

//---------------------------------------------------------------
EditScriptView::~EditScriptView()
{

}

//---------------------------------------------------------------
void EditScriptView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}


//---------------------------------------------------------------
void EditScriptView::Draw(BRect update)
{

}

//---------------------------------------------------------------
void EditScriptView::CheckNotify()
{
	if (mRunScriptBox->Value())
	{
	mHourMenuField->SetEnabled(true);
	mMinuteMenuField->SetEnabled(true);
	}
	else
	{
	mHourMenuField->SetEnabled(false);
	mMinuteMenuField->SetEnabled(false);
	}

}

//---------------------------------------------------------------
void EditScriptView::History()
{
MSave Save("save");
BPath fPath;
BString tempString;
BString tempString2;
BString tempString3;
BString FilePath;

find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &fPath);
tempString.SetTo(fPath.Path());
tempString.Append(SAVE_HISTORY_PATH);
fPath = tempString.String();
	for (int a = 1; a <= INT_MAXFILES; a++)
	{
	tempString2.SetTo("");
	tempString2 << "Script-" << a;
	
	FilePath.SetTo(fPath.Path());
	FilePath << tempString2.String();
	
	BEntry Entry(FilePath.String());
		if (Entry.Exists())
		{
		//The file is there!!!
		Save.FindString(FilePath.String(), SAVE_FILE_TITLE, &tempString2, "M_ERROR");
		Save.FindString(FilePath.String(), SAVE_FILE_NOTE, &tempString3, "M_ERROR");
			if (strcmp(tempString2.String(), "M_ERROR") && strcmp(tempString3.String(), "M_ERROR"))
			{
			mHistoryMenu->AddItem(mMenuItem = new BMenuItem(tempString2.String(), new BMessage(MSG_HISTORY_SCRIPT_ITEM_SELECTED)));
			}
		}
	}
//mHistoryMenu->RemoveItem(mHistoryMenu->CountItems() - 1);
}

//---------------------------------------------------------------
void EditScriptView::GetPathOfSelectedFile(BString *StrPath)
{
int selectedItemNumber;
BString tempString;
BString tempString2;
BString FilePath;
BPath Path;
int ItemNumber = 1;
MSave Save("Save");

find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
tempString.SetTo(Path.Path());
tempString.Append(SAVE_HISTORY_PATH);
	for (int a = 1; a <= INT_MAXFILES; a++)
	{
	FilePath.SetTo(tempString.String());
	FilePath << "Script-" << a;

	BEntry Entry(FilePath.String());
		if (Entry.Exists())
		{
		Save.FindString(FilePath.String(), SAVE_FILE_TYPE, &tempString2, "M_ERROR");
			if (!strcmp(tempString2.String(), "Script"))
			{
				if (mHistoryMenu->ItemAt(ItemNumber - 1)->IsMarked())
				{
				StrPath->SetTo(FilePath.String());
				ItemNumber++;
				a = 101;
				}
				else
				{
				ItemNumber++;
				}
			}
		}
	}
}




