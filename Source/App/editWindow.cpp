//-----------------------  Local includes  ----------------------
#include "editWindow.h"

//----------------------- Global includes  ----------------------


//---------------------------------------------------------------
EditWindow::EditWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags)
			 : BWindow(frame, title, B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL, B_NOT_RESIZABLE)
{

fFrame.Set(frame.left, frame.top, frame.right, frame.bottom);

	//Use the scriptview
	if (!strcmp(Title(), STR_ADD_SCRIPT_WIN[INT_LANGUAGE]) || !strcmp(Title(), STR_EDIT_SCRIPT_WIN[INT_LANGUAGE]))
	{
	
	}
	//Use the noteview
	if (!strcmp(Title(), STR_ADD_NOTE_WIN[INT_LANGUAGE]) || !strcmp(Title(), STR_EDIT_NOTE_WIN[INT_LANGUAGE]))
	{
	
	}
	//Use the apointmentview
	if (!strcmp(Title(), STR_ADD_APOINTMENT_WIN[INT_LANGUAGE]) || !strcmp(Title(), STR_EDIT_APOINTMENT_WIN[INT_LANGUAGE]))
	{
	
	}
}

//---------------------------------------------------------------
EditWindow::~EditWindow()
{

}

//---------------------------------------------------------------
void EditWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	//Add view messages
	case MSG_ADD_SCRIPT_WIN:
		_EditScriptView = new EditScriptView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
							 "_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW);
		_EditScriptView->mTextView->SetText("#!/bin/sh\n");
		AddChild(_EditScriptView);
		_EditScriptView->MakeFocus(true);
		fType.SetTo("Script");

		message->FindInt32("Year", &fYear);
		message->FindInt32("Month", &fMonth);
		message->FindInt32("Day", &fDay);
	break;
	case MSG_EDIT_SCRIPT_WIN:
		message->FindString(SAVE_FILE_TYPE, &fType);
		message->FindString(SAVE_FILE_TITLE, &fTitle);
		message->FindString(SAVE_FILE_TIME, &fTime);
		message->FindString(SAVE_FILE_NOTE, &fNote);
		message->FindString(SAVE_FILE_PATH, &fPath);
		message->FindString(SAVE_FILE_NOTIFY, &fNotify);
			if (!strcmp(fNotify.String(), "true"))
			{	
			_EditScriptView = new EditScriptView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
						 "_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW, fTitle.String(), fTime.String(),
						 fNote.String(), true);
			}
			else
			{
			_EditScriptView = new EditScriptView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
						 "_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW, fTitle.String(), fTime.String(),
						 fNote.String(), false);
			}
		AddChild(_EditScriptView);
		_EditScriptView->MakeFocus(true);
		
	break;
	case MSG_ADD_NOTE_WIN:
		_EditNoteView = new EditNoteView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
						 "_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW);
		AddChild(_EditNoteView);
		_EditNoteView->MakeFocus(true);
		fType.SetTo("Note");
		
		message->FindInt32("Year", &fYear);
		message->FindInt32("Month", &fMonth);
		message->FindInt32("Day", &fDay);
	break;
	case MSG_EDIT_NOTE_WIN:
		message->FindString(SAVE_FILE_TYPE, &fType);
		message->FindString(SAVE_FILE_TITLE, &fTitle);
		message->FindString(SAVE_FILE_TIME, &fTime);
		message->FindString(SAVE_FILE_NOTE, &fNote);
		message->FindString(SAVE_FILE_PATH, &fPath);
		message->FindString(SAVE_FILE_NOTIFY, &fNotify);
	
		_EditNoteView = new EditNoteView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
						 "_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW, fTitle.String(), fNote.String());
		AddChild(_EditNoteView);
		_EditNoteView->MakeFocus(true);
	
	break;
	case MSG_ADD_APOINTMENT_WIN:
		_EditApointmentView = new EditApointmentView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
						"_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW);
		AddChild(_EditApointmentView);
		_EditApointmentView->MakeFocus(true);
		fType.SetTo("Apointment");
	
		message->FindInt32("Year", &fYear);
		message->FindInt32("Month", &fMonth);
		message->FindInt32("Day", &fDay);
	break;
	case MSG_EDIT_APOINTMENT_WIN:
		message->FindString(SAVE_FILE_TYPE, &fType);
		message->FindString(SAVE_FILE_TITLE, &fTitle);
		message->FindString(SAVE_FILE_TIME, &fTime);
		message->FindString(SAVE_FILE_NOTE, &fNote);
		message->FindString(SAVE_FILE_PATH, &fPath);
		message->FindString(SAVE_FILE_NOTIFY, &fNotify);
			if (!strcmp(fNotify.String(), "true"))
			{
			_EditApointmentView = new EditApointmentView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
						 "_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW, fTitle.String(), fTime.String(),
						 fNote.String(), true);
			}
			else
			{
			_EditApointmentView = new EditApointmentView(BRect(0, 0, fFrame.right - fFrame.left, fFrame.bottom - fFrame.top),
						 "_EditScriptView", B_FOLLOW_ALL, B_NAVIGABLE | B_WILL_DRAW, fTitle.String(), fTime.String(),
						 fNote.String(), false);
			}
		AddChild(_EditApointmentView);
		_EditApointmentView->MakeFocus(true);
		
	break;
	//Here comes the savemessages
	case MSG_SAVE_SCRIPT:
		SaveScript();
	break;
	case MSG_SAVE_NOTE:
		SaveNote();
	break;
	case MSG_SAVE_APOINTMENT:
		SaveApointment();
	break;
	case MSG_CANCEL:
		QuitRequested();
	break;
	case MSG_RUN_SCRIPT_CHECKBOX:
		_EditScriptView->CheckNotify();
	break;
	case MSG_NOTIFY_APOINTMENT_CHECKBOX:
		_EditApointmentView->CheckNotify();
	break;
	case MSG_HISTORY_SCRIPT_ITEM_SELECTED:
	{
	Lock();
		BString FilePath;
		MSave Save("Save");
		_EditScriptView->GetPathOfSelectedFile(&FilePath);
		
		//Title
		Save.FindString(FilePath.String(), SAVE_FILE_TITLE, &tmpString, "M_ERROR");
		_EditScriptView->mTitleControl->SetText(tmpString.String());
		//Note
		Save.FindString(FilePath.String(), SAVE_FILE_NOTE, &tmpString, "M_ERROR");
		_EditScriptView->mTextView->SetText(tmpString.String());
		//Run?
		Save.FindString(FilePath.String(), SAVE_FILE_NOTIFY, &tmpString, "M_ERROR");
			if (!strcmp(tmpString.String(), "true"))
			{
			_EditScriptView->mRunScriptBox->SetValue(true);
			}
			else
			{
			_EditScriptView->mRunScriptBox->SetValue(false);
			}
		//Hour
		Save.FindString(FilePath.String(), SAVE_FILE_TIME, &tmpString, "M_ERROR");
		tmpString.Remove(tmpString.FindFirst(":"), tmpString.CountChars() - tmpString.FindFirst(":"));
		_EditScriptView->mHourMenu->ItemAt(atoi(tmpString.String()))->SetMarked(true);
		//Minute
		Save.FindString(FilePath.String(), SAVE_FILE_TIME, &tmpString, "M_ERROR");
		tmpString.Remove(0, tmpString.FindFirst(":") + 1);
		_EditScriptView->mMinuteMenu->ItemAt(atoi(tmpString.String()))->SetMarked(true);
	Unlock();
	break;
	}
	default:
	
	break;
	}
}

//---------------------------------------------------------------
bool EditWindow::QuitRequested()
{
	//Scriptwindow
	if (!strcmp(Title(), STR_ADD_SCRIPT_WIN[INT_LANGUAGE]) || !strcmp(Title(), STR_EDIT_SCRIPT_WIN[INT_LANGUAGE]))
	{
	BAlert * mAlert = new BAlert("mAlert", STR_SAVE_CHANGES[INT_LANGUAGE], STR_DONT_SAVE[INT_LANGUAGE], STR_CANCEL[INT_LANGUAGE], STR_SAVE[INT_LANGUAGE]);
		if (strcmp(_EditScriptView->mTextView->Text(), fNote.String()) || strcmp(_EditScriptView->mTitleControl->Text(), fTitle.String()))
		{
			switch (mAlert->Go())
			{
			case 2:
				PostMessage(MSG_SAVE_SCRIPT);
				break;
			case 1:
				//Cancel (nothing happends)
			break;
			case 0:
				//Close();
				//return(1);
			break;
			default:
			
			break;
			}
		}
		else
		{
		delete mAlert;
		//Close();
		//return(1);
		}
	}
	//NoteWindow
	if (!strcmp(Title(), STR_ADD_NOTE_WIN[INT_LANGUAGE]) || !strcmp(Title(), STR_EDIT_NOTE_WIN[INT_LANGUAGE]))
	{
	BAlert * mAlert = new BAlert("mAlert", STR_SAVE_CHANGES[INT_LANGUAGE], STR_DONT_SAVE[INT_LANGUAGE], STR_CANCEL[INT_LANGUAGE], STR_SAVE[INT_LANGUAGE]);
		if (strcmp(_EditNoteView->mTextView->Text(), fNote.String()) || strcmp(_EditNoteView->mTitleControl->Text(), fTitle.String()))
		{
			switch (mAlert->Go())
			{
			case 2:
				PostMessage(MSG_SAVE_NOTE);
				break;
			case 1:
				//Cancel (nothing happends)
			break;
			case 0:
				//Close();
				//return(1);
			break;
			default:
			
			break;
			}
		}
		else
		{
		delete mAlert;
		//Close();
		//return(1);
		}
	}
	//Apointmentwindow
	if (!strcmp(Title(), STR_ADD_APOINTMENT_WIN[INT_LANGUAGE]) || !strcmp(Title(), STR_EDIT_APOINTMENT_WIN[INT_LANGUAGE]))
	{
	BAlert * mAlert = new BAlert("mAlert", STR_SAVE_CHANGES[INT_LANGUAGE], STR_DONT_SAVE[INT_LANGUAGE], STR_CANCEL[INT_LANGUAGE], STR_SAVE[INT_LANGUAGE]);
		if (strcmp(_EditApointmentView->mTextView->Text(), fNote.String()) || strcmp(_EditApointmentView->mTitleControl->Text(), fTitle.String()))
		{
			switch (mAlert->Go())
			{
			case 2:
				PostMessage(MSG_SAVE_APOINTMENT);
				break;
			case 1:
				//Cancel (nothing happends)
			break;
			case 0:
				//Close();
				//return(1);
			break;
			default:
			
			break;
			}
		}
		else
		{
		delete mAlert;
		//Close();
		//return(1);
		}
	}
}

//---------------------------------------------------------------
void EditWindow::SaveNote()
{
BString FilePath;
	if (!strcmp(_EditNoteView->mTitleControl->Text(), ""))
	{
	BAlert * mAlert = new BAlert("mAlert", STR_MISSING_TITLE[INT_LANGUAGE], STR_OK[INT_LANGUAGE]);
	mAlert->Go();
	}
	else
	{
	MSave Save("save");
		if(!strcmp(fPath.String(), ""))
		{
		find_directory(B_COMMON_SETTINGS_DIRECTORY, &Path);
		fPath.SetTo(Path.Path());
		fPath.Append(SAVE_NOTE_PATH);
		Path = fPath.String();
			for (int a = 1; a <= INT_MAXFILES; a++)
			{
			fFileName.SetTo("");
			fFileName << fDay << "-" << fMonth << fYear << "-" << a;
			FilePath.SetTo(fPath.String());
			FilePath << fFileName.String();
			BEntry Entry(FilePath.String());
				if (!Entry.Exists())
				{
				Save.AddString(FilePath.String(), SAVE_FILE_TITLE, _EditNoteView->mTitleControl->Text(), true);
				Save.AddString(FilePath.String(), SAVE_FILE_NOTE, _EditNoteView->mTextView->Text(), true);
				Save.AddString(FilePath.String(), SAVE_FILE_TYPE, "Note", true);
				Save.AddString(FilePath.String(), SAVE_FILE_TIME, "12:00", true);
				Save.AddString(FilePath.String(), SAVE_FILE_NOTIFY, "true", true);
				a = 101;
				}
				if (a == 100)
				{
				BAlert * mAlert = new BAlert("error", "Warning!", "No available filenames found,\nhave you REALLY saved 100 notes / apointments / scripts on a single day?\n Wow you ARE busy", "ok");
				mAlert->Go();
				}
			}
		}
		else
		{
		fPath.Remove(fPath.FindLast("/") + 1, fPath.CountChars());
		Save.AddString(fPath.String(), SAVE_FILE_TITLE, _EditNoteView->mTitleControl->Text(), true);
		Save.AddString(fPath.String(), SAVE_FILE_NOTE, _EditNoteView->mTextView->Text(), true);
		Save.AddString(fPath.String(), SAVE_FILE_TYPE, "Note", true);
		Save.AddString(fPath.String(), SAVE_FILE_TIME, "12:00", true);
		Save.AddString(fPath.String(), SAVE_FILE_NOTIFY, "true", true);
		}
	fPath.SetTo("");
	be_app->PostMessage(MSG_GET_NOTES);
	Close();
	}
}
	
//---------------------------------------------------------------
void EditWindow::SaveScript()
{
BString FilePath;
BEntry Entry("/boot/home");
	if (!strcmp(_EditScriptView->mTitleControl->Text(), ""))
	{
	BAlert * mAlert = new BAlert("mAlert", STR_MISSING_TITLE[INT_LANGUAGE], STR_OK[INT_LANGUAGE]);
	mAlert->Go();
	}
	else
	{
	MSave Save("save");
		if(!strcmp(fPath.String(), ""))
		{
		find_directory(B_COMMON_SETTINGS_DIRECTORY, &Path);
		fPath.SetTo(Path.Path());
		fPath.Append(SAVE_NOTE_PATH);
		Path = fPath.String();
			for (int a = 1; a <= INT_MAXFILES; a++)
			{
			fFileName.SetTo("");
			fFileName << fDay << "-" << fMonth << fYear << "-" << a;
			FilePath.SetTo(fPath.String());
			FilePath << fFileName.String();
			Entry.SetTo(FilePath.String());
				if (!Entry.Exists())
				{
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TITLE, _EditScriptView->mTitleControl->Text(), true);
				Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTE, _EditScriptView->mTextView->Text(), true);
				
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TYPE, "Script", true);
				tmpString2.SetTo("");
				tmpString2 << _EditScriptView->mHourMenu->ItemAt(_EditScriptView->mHourMenu->IndexOf(_EditScriptView->mHourMenu->FindMarked()))->Label() << ":" << _EditScriptView->mMinuteMenu->ItemAt(_EditScriptView->mMinuteMenu->IndexOf(_EditScriptView->mMinuteMenu->FindMarked()))->		Label();
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TIME, tmpString2.String(), true);
					if (_EditScriptView->mRunScriptBox->Value())
					{
					Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "true", true);
					}
					else
					{
					Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "false", true);
					}
				a = 101;
				}
				if (a == 100)
				{
				BAlert * mAlert = new BAlert("error", "Warning!", "No available filenames found,\nhave you REALLY saved 100 notes / apointments / scripts on a single day?\n Wow you ARE busy", "ok");
				mAlert->Go();
				}
			}
		}
		//Its add
		else
		{
		fPath.Remove(fPath.FindLast("/") + 1, fPath.CountChars());
		Save.AddString(fPath.String(), SAVE_FILE_TITLE, _EditScriptView->mTitleControl->Text(), true);
		Save.AddString(fPath.String(), SAVE_FILE_NOTE, _EditScriptView->mTextView->Text(), true);
			
		Save.AddString(fPath.String(), SAVE_FILE_TYPE, "Script", true);
		tmpString2.SetTo("");
		tmpString2 << _EditScriptView->mHourMenu->ItemAt(_EditScriptView->mHourMenu->IndexOf(_EditScriptView->mHourMenu->FindMarked()))->Label() << ":" << _EditScriptView->mMinuteMenu->ItemAt(_EditScriptView->mMinuteMenu->IndexOf(_EditScriptView->mMinuteMenu->FindMarked()))->Label();
		Save.AddString(fPath.String(), SAVE_FILE_TIME, tmpString2.String(), true);
			if (_EditScriptView->mRunScriptBox->Value())
			{
			Save.AddString(fPath.String(), SAVE_FILE_NOTIFY, "true", true);
			}
			else
			{
			Save.AddString(fPath.String(), SAVE_FILE_NOTIFY, "false", true);
			}
		}
	fPath.SetTo("");
	}
	
//Save to history aswell
	if (!strcmp(_EditScriptView->mTitleControl->Text(), ""))
	{
	BAlert * mAlert = new BAlert("mAlert", STR_MISSING_TITLE[INT_LANGUAGE], STR_OK[INT_LANGUAGE]);
	mAlert->Go();
	}
	else
	{
	MSave Save("save");
		if(!strcmp(fPath.String(), ""))
		{
		find_directory(B_COMMON_SETTINGS_DIRECTORY, &Path);
		fPath.SetTo(Path.Path());
		fPath.Append(SAVE_HISTORY_PATH);
		Path = fPath.String();
			for (int a = 1; a <= INT_MAXFILES; a++)
			{
			fFileName.SetTo("Script-");
			fFileName << a;
			FilePath.SetTo(fPath.String());
			FilePath << fFileName.String();
			Entry.SetTo(FilePath.String());
		
				if (!Entry.Exists())
				{
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TITLE, _EditScriptView->mTitleControl->Text(), true);
				Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTE, _EditScriptView->mTextView->Text(), true);
			
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TYPE, "Script", true);
				tmpString2.SetTo("");
				tmpString2 << _EditScriptView->mHourMenu->ItemAt(_EditScriptView->mHourMenu->IndexOf(_EditScriptView->mHourMenu->FindMarked()))->Label() << ":" << _EditScriptView->mMinuteMenu->ItemAt(_EditScriptView->mMinuteMenu->IndexOf(_EditScriptView->mMinuteMenu->FindMarked()))->Label();
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TIME, tmpString2.String(), true);
					if (_EditScriptView->mRunScriptBox->Value())
					{
					Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "true", true);
					}
					else
					{
					Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "false", true);
					}
				a = 101;
				}
				if (a == 100)
				{
				BAlert * mAlert = new BAlert("error", "Warning!", "No available filenames found,\nhave you REALLY saved 100 notes / apointments / scripts on a single day?\n Wow you ARE busy", "ok");
				mAlert->Go();
				}
			}
		}
		//Its Add
		else
		{
		fPath.Remove(fPath.FindLast("/") + 1, fPath.CountChars());
		Save.AddString(Path, fFileName.String(), SAVE_FILE_TITLE, _EditScriptView->mTitleControl->Text(), true);
		Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTE, _EditScriptView->mTextView->Text(), true);
		
		Save.AddString(Path, fFileName.String(), SAVE_FILE_TYPE, "Script", true);
		tmpString2.SetTo("");
		tmpString2 << _EditScriptView->mHourMenu->ItemAt(_EditScriptView->mHourMenu->IndexOf(_EditScriptView->mHourMenu->FindMarked()))->Label() << ":" << _EditScriptView->mMinuteMenu->ItemAt(_EditScriptView->mMinuteMenu->IndexOf(_EditScriptView->mMinuteMenu->FindMarked()))->Label();
		Save.AddString(Path, fFileName.String(), SAVE_FILE_TIME, tmpString2.String(), true);
			if (_EditScriptView->mRunScriptBox->Value())
			{
			Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "true", true);
			}
			else
			{
			Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "false", true);
			}
		}
	fPath.SetTo("");
	be_app->PostMessage(MSG_GET_NOTES);
	Close();
	}
}
	
//---------------------------------------------------------------
void EditWindow::SaveApointment()
{
BEntry Entry;
BString FilePath;
	if (!strcmp(_EditApointmentView->mTitleControl->Text(), ""))
	{
	BAlert * mAlert = new BAlert("mAlert", STR_MISSING_TITLE[INT_LANGUAGE], STR_OK[INT_LANGUAGE]);
	mAlert->Go();
	}
	else
	{
	MSave Save("save");
		if(!strcmp(fPath.String(), ""))
		{
		find_directory(B_COMMON_SETTINGS_DIRECTORY, &Path);
		fPath.SetTo(Path.Path());
		fPath.Append(SAVE_NOTE_PATH);
		Path = fPath.String();
			for (int a = 1; a <= INT_MAXFILES; a++)
			{
			fFileName.SetTo("");
			fFileName << fDay << "-" << fMonth << fYear << "-" << a;
			FilePath.SetTo(fPath.String());
			FilePath << fFileName.String();
			Entry.SetTo(FilePath.String());
		
				if (!Entry.Exists())
				{
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TITLE, _EditApointmentView->mTitleControl->Text(), true);
				Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTE, _EditApointmentView->mTextView->Text(), true);
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TYPE, "Apointment", true);
				tmpString2.SetTo("");
				tmpString2 << _EditApointmentView->mHourMenu->ItemAt(_EditApointmentView->mHourMenu->IndexOf(_EditApointmentView->mHourMenu->FindMarked()))->Label() << ":" << _EditApointmentView->mMinuteMenu->ItemAt(_EditApointmentView->mMinuteMenu->IndexOf(_EditApointmentView->mMinuteMenu->FindMarked()))->Label();
				Save.AddString(Path, fFileName.String(), SAVE_FILE_TIME, tmpString2.String(), true);
					if (_EditApointmentView->mNotifyBox->Value())
					{
					Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "true", true);
					}
					else
					{
					Save.AddString(Path, fFileName.String(), SAVE_FILE_NOTIFY, "false", true);
					}
				a = 101;
				}
				if (a == 100)
				{
				BAlert * mAlert = new BAlert("error", "Warning!", "No available filenames found,\nhave you REALLY saved 100 notes / apointments / scripts on a single day?\n Wow you ARE busy", "ok");
				mAlert->Go();
				}
			}
		}
		//its add
		else
		{
		fPath.Remove(fPath.FindLast("/") + 1, fPath.CountChars());
		Save.AddString(fPath.String(), SAVE_FILE_TITLE, _EditApointmentView->mTitleControl->Text(), true);
		Save.AddString(fPath.String(), SAVE_FILE_NOTE, _EditApointmentView->mTextView->Text(), true);
		Save.AddString(fPath.String(), SAVE_FILE_TYPE, "Apointment", true);
		tmpString2.SetTo("");
		tmpString2 << _EditApointmentView->mHourMenu->ItemAt(_EditApointmentView->mHourMenu->IndexOf(_EditApointmentView->mHourMenu->FindMarked()))->Label() << ":" << _EditApointmentView->mMinuteMenu->ItemAt(_EditApointmentView->mMinuteMenu->IndexOf(_EditApointmentView->mMinuteMenu->FindMarked()))->Label();
		Save.AddString(fPath.String(), SAVE_FILE_TIME, tmpString2.String(), true);
			if (_EditApointmentView->mNotifyBox->Value())
			{
			Save.AddString(fPath.String(), SAVE_FILE_NOTIFY, "true", true);
			}
			else
			{
			Save.AddString(fPath.String(), SAVE_FILE_NOTIFY, "false", true);
			}
		}
	fPath.SetTo("");
	be_app->PostMessage(MSG_GET_NOTES);
	Close();
	}
}


