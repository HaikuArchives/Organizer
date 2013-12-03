//-----------------------  Local includes  ----------------------
#include "main.h"

//----------------------- Global includes  ----------------------


//---------------------------------------------------------------
int main(int32 argc, char** argv)
{
//We save the execDir to the settings file
BPath path;
BString tmp;
MSave savefile("savefile");
find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &path);
tmp.SetTo(path.Path());
tmp.Append(SAVE_SETTINGS_PATH);
path.SetTo(tmp.String());
tmp.SetTo(argv[0]);
tmp.RemoveLast(STR_EXEC_FILE_NAME);
savefile.AddString(path, SAVE_FILE_NAME, NAME_EXEC_DIR, tmp.String(), true);

new mApp();
be_app->Run();
return(0);
}

//---------------------------------------------------------------
mApp::mApp()
		: BApplication(ApplicationSignature)
{
//Load settings
LoadSettings();
}

//---------------------------------------------------------------
/*mApp::QuitRequested()
{

}*/

//---------------------------------------------------------------
mApp::~mApp()
{
delete _mWindow;
delete _AboutWindow;
delete _PreferencesWindow;
delete _EditWindow;
delete _ExportWindow;
delete _Wind;
}

//---------------------------------------------------------------
void mApp::ReadyToRun()
{
RunNotification = true;
//Make all the needed folders
/********************************************
*\settings-
			\fSub-
					\Organizer-
								\Settings
								\Notes
*********************************************/
//Make sure all the folders are there
find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &path);
//Make fSub folder
tmp.SetTo("mkdir ");
tmp.Append(path.Path());
tmp.Append(SAVE_PATH_PART_1);
tmp.Append(" &");
system(tmp.String());
//Make Organizer folder
tmp.RemoveLast(" &");
tmp.Append(SAVE_PATH_PART_2);
tmp.Append(" &");
system(tmp.String());
//Make Settings folder
tmp.RemoveLast(" &");
tmp.Append(SAVE_PATH_PART_3_1);
tmp.Append(" &");
system(tmp.String());
//Make Apointments folder
tmp.RemoveLast(" &");
tmp.RemoveLast(SAVE_PATH_PART_3_1);
tmp.Append(SAVE_PATH_PART_3_2);
tmp.Append(" &");
system(tmp.String());
//Make History folder
tmp.RemoveLast(" &");
tmp.RemoveLast(SAVE_PATH_PART_3_2);
tmp.Append(SAVE_PATH_PART_3_3);
tmp.Append(" &");
system(tmp.String());

//show main window
_mWindow = new mWindow();
	if (_mWindow != NULL)
	{
	_mWindow->Show();
	}
	else
	{
	be_app->PostMessage(B_QUIT_REQUESTED);
	}
	
//Check for notifications
Notification = spawn_thread(NotificationThread_static, "NotificationThread",
										B_LOW_PRIORITY, this);
resume_thread(Notification);
//Check for updates
CheckForUpdate = spawn_thread(CheckForUpdateThread_static, "Check For Updates",
										B_NORMAL_PRIORITY, this);
resume_thread(CheckForUpdate);

}


//----------------------------------------------------------------
void mApp::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	case MSG_EXPORT_HTML:
		Show = true;
		for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_EXPORT_WINDOW[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_ExportWindow = new ExportWindow(BRect(100, 100, 550, 500), STR_EXPORT_WINDOW[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE, _mWindow->_CalenderView->mCalender->Month(), _mWindow->_CalenderView->mCalender->Year());
			_ExportWindow->Show();
			}
			else
			{
			_ExportWindow->Activate();
			}
	
	break;
	case MSG_ABOUT:
		//show about window
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_ABOUT_WINDOW[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_AboutWindow = new AboutWindow(BRect(100, 100, 550, 500), STR_ABOUT_WINDOW[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_AboutWindow->Show();
			}
			else
			{
			_AboutWindow->Activate();
			}
	break;
	case MSG_PREFERENCES:
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_PREFERENCES_WINDOW[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_PreferencesWindow = new PreferencesWindow(BRect(100, 100, 500, 500), STR_PREFERENCES_WINDOW[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_PreferencesWindow->Show();
			}
			else
			{
			_PreferencesWindow->Activate(true);
			}
	break;
	case MSG_ADD_SCRIPT_WIN:
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_ADD_SCRIPT_WIN[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_EditWindow =  new EditWindow(BRect(100, 100, 500, 500), STR_ADD_SCRIPT_WIN[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_EditWindow->Show();
			_EditWindow->PostMessage(message);
			}
			else
			{
			_EditWindow->Activate();
			}
	break;
	case MSG_EDIT_SCRIPT_WIN:
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_EDIT_SCRIPT_WIN[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_EditWindow =  new EditWindow(BRect(100, 100, 500, 500), STR_EDIT_SCRIPT_WIN[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_EditWindow->Show();
			_EditWindow->PostMessage(message);
			}
			else
			{
			_EditWindow->Activate();
			}
	break;
	case MSG_ADD_NOTE_WIN:
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_ADD_NOTE_WIN[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_EditWindow =  new EditWindow(BRect(100, 100, 500, 500), STR_ADD_NOTE_WIN[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_EditWindow->Show();
			_EditWindow->PostMessage(message);
			}
			else
			{
			_EditWindow->Activate();
			}
	break;
	case MSG_EDIT_NOTE_WIN:
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_EDIT_NOTE_WIN[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_EditWindow =  new EditWindow(BRect(100, 100, 500, 500), STR_EDIT_NOTE_WIN[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_EditWindow->Show();
			_EditWindow->PostMessage(message);
			}
			else
			{
			_EditWindow->Activate();
			}
	break;
	case MSG_ADD_APOINTMENT_WIN:
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_ADD_APOINTMENT_WIN[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_EditWindow =  new EditWindow(BRect(100, 100, 500, 500), STR_ADD_APOINTMENT_WIN[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_EditWindow->Show();
			_EditWindow->PostMessage(message);
			}
			else
			{
			_EditWindow->Activate();
			}
	break;
	case MSG_EDIT_APOINTMENT_WIN:
		Show = true;
			for (int a = 1; a <= CountWindows(); a++)
			{
				if (!strcmp(WindowAt(a - 1)->Title(), STR_EDIT_APOINTMENT_WIN[INT_LANGUAGE]))
				{
				Show = false;
				}
			}
			if (Show)
			{
			_EditWindow =  new EditWindow(BRect(100, 100, 500, 500), STR_EDIT_APOINTMENT_WIN[INT_LANGUAGE], B_FOLLOW_ALL, B_NOT_RESIZABLE);
			_EditWindow->Show();
			_EditWindow->PostMessage(message);
			}
			else
			{
			_EditWindow->Activate();
			}
	break;
	//Reload the listview
	case MSG_GET_NOTES:
		_mWindow->LockLooper();
		_mWindow->GetNotes();
		_mWindow->UnlockLooper();
	break;
	case MSG_CALENDER_STYLE:
	{
		_mWindow->LockLooper();
		_mWindow->_CalenderView->mCalender->SetAmericanStyleCalender(_PreferencesWindow->_PreferencesView->mCalenderStyleCheckBox->Value());
		_mWindow->Activate();
		_mWindow->UnlockLooper();
		snooze(30000);
		_PreferencesWindow->LockLooper();
		_PreferencesWindow->Activate();
		_PreferencesWindow->UnlockLooper();
		
		MSave save("save");
		_mWindow->GetSettingsPath(&path);
		//Save Style
		save.AddBool(path, SAVE_FILE_NAME, NAME_CALENDER_STYLE, _PreferencesWindow->_PreferencesView->mCalenderStyleCheckBox->Value(), true);
	break;
	}
	case MSG_CALENDER_COLORFUL:
	{
		_mWindow->_CalenderView->mCalender->SetColorfulCalender(_PreferencesWindow->_PreferencesView->mCalenderColorCheckBox->Value());
		_mWindow->LockLooper();
		_mWindow->_CalenderView->mCalender->Draw(BRect(0, 0, 1600, 1200));
		_mWindow->Activate();
		_mWindow->UnlockLooper();
		snooze(30000);
		_PreferencesWindow->LockLooper();
		_PreferencesWindow->Activate();
		_PreferencesWindow->UnlockLooper();
		
		MSave save("save");
		_mWindow->GetSettingsPath(&path);
		//Save Style
		save.AddBool(path, SAVE_FILE_NAME, NAME_CALENDER_COLORFUL, _PreferencesWindow->_PreferencesView->mCalenderColorCheckBox->Value(), true);
	break;
	}
	case MSG_OPEN_GL_GAME:
		_Wind = new Wind(STR_HIDDEN_OPENGL_GAME[INT_LANGUAGE]);
	break;
	case MSG_CLOSE_GL_GAME:
		_Wind->Lock();
		_Wind->Close();
	break;
	case MSG_LANGUAGE_CHANGED:
	{
			MSave save("save");
			_mWindow->GetSettingsPath(&path);
			
			save.AddInt32(path, SAVE_FILE_NAME, NAME_LANGUAGE, _PreferencesWindow->_PreferencesView->mLanguageMenu->IndexOf(_PreferencesWindow->_PreferencesView->mLanguageMenu->FindMarked()), true);
			
			if (_PreferencesWindow->_PreferencesView->mLanguageMenu->IndexOf(_PreferencesWindow->_PreferencesView->mLanguageMenu->FindMarked()) != INT_LANGUAGE)
			{
			BAlert * mAlert = new BAlert("mAlert", STR_LANGUAGE_ALERT[INT_LANGUAGE], STR_RESTART_NOW[INT_LANGUAGE], STR_RESTART_LATER[INT_LANGUAGE]);
				switch(mAlert->Go())
				{
				case 0:
				{
					BString tempString;
					BString tempString2;
					BPath Path;
					find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
					tempString.SetTo(path.Path());
					tempString.Append(SAVE_SETTINGS_PATH);
					save.FindString(tempString.String(), SAVE_FILE_NAME, NAME_EXEC_DIR, &tempString2, "M_ERROR");
					tempString2.Append(SAVE_SCRIPT_PATH);
					tempString2 << "Restart &";
					system(tempString2.String());
				break;
				}
				default:
				
				break;
				}
			}
	break;
	}
	case MSG_EXPORT_HTML_FILE:
	{
	mFilePanel = new BFilePanel(B_OPEN_PANEL, NULL, NULL, B_DIRECTORY_NODE,
	//mFilePanel = new BFilePanel(B_OPEN_PANEL, NULL, NULL, B_FILE_NODE,
					false, NULL , NULL, false, true); 
	mFilePanel->Window()->SetTitle("Save To: ");
	mFilePanel->Show();
	break;
	}
	case MSG_QUIT_PLEASE:
		RunNotification = false;
		//status_t junk;
		kill_thread(Notification);
		kill_thread(CheckForUpdate);
			while (CountWindows() > 0)
			{
			//WindowAt(CountWindows() - 1)->Lock();
			WindowAt(CountWindows() - 1)->Close();
			}
	break;
	default:
	
	break;
	}
}

//-----------------------------------------------------------------
void mApp::RefsReceived(BMessage *message)
{
cout << "REFS RECIEVED!! " << endl;
//Get Filepanelpath
int32	count = 0;
uint32	type = 0;
message->GetInfo("refs", &type, &count);
cout << "type is " << type << "count is " << count << endl;
	for (int32 i = 0; i < count; i++) 
	{
	entry_ref	ref;
	cout << " asd its " << i << endl;
		if (message->FindRef("refs", i, &ref) == B_NO_ERROR) 
		{
		BEntry entry(&ref);
			if (entry.InitCheck() == B_NO_ERROR) 
			{
			BPath Path;
			entry.GetPath(&Path);
			LockLooper();
			_ExportWindow->fSaveTo.SetTo(Path.Path());
			UnlockLooper();
			}
			else
			{
			cout << "2_" << endl;
			}
		}
		else
		{
		cout << "1_" << endl;
		}
	}
}

//----------------------------------------------------------------
void mApp::LoadSettings()
{
MSave load("load");
_mWindow->GetSettingsPath(&path);
int32 temp;
int32 temp2;
bool temp3;

temp2 = INT_LANGUAGE;
//Load Language
load.FindInt32(path, SAVE_FILE_NAME, NAME_LANGUAGE, &temp, temp2);
INT_LANGUAGE = temp;

temp2 = INT_THEME;
//Load Theme
load.FindInt32(path, SAVE_FILE_NAME, NAME_THEME, &temp, temp2);
INT_THEME = temp;

//Load CalenderStyle
load.FindBool(path, SAVE_FILE_NAME, NAME_CALENDER_STYLE, &temp3, false);
BOOL_AMERICAN_STYLE = temp3;

//Load CalenderColorThing
load.FindBool(path, SAVE_FILE_NAME, NAME_CALENDER_COLORFUL, &temp3, true);
BOOL_COLORFUL_CALENDER = temp3;
}

//----------------------------------------------------------------
//Check for updates
int32
mApp::CheckForUpdateThread_static(void *data)
{
	mApp *check4updates = (mApp *)data;
	//check4updates->CheckForUpdateThread();
	return 0;
}

//----------------------------------------------------------------
void mApp::CheckForUpdateThread()
{
sleep(10);
MSave savefile("savefile");
_mWindow->GetSettingsPath(&path);
savefile.FindBool(path, SAVE_FILE_NAME, "CheckForUpdates", &CheckForUpdates, true);

	if (CheckForUpdates)
	{
	tmp.SetTo("wget ");
	tmp.Append(SAVE_UPDATE_VERSION);
	tmp.Append(" ");
	tmp.Append(GET_NEW_VERSION_PATH);
	tmp.Append(" &");
	system(tmp.String());
	
	tmp.SetTo("wget ");
	tmp.Append(SAVE_UPDATE_URL);
	tmp.Append(" ");
	tmp.Append(GET_NEW_URL_PATH);
	tmp.Append(" &");
	system(tmp.String());
	sleep(10);

	FILE* file_version = fopen(SAVE_UPDATE_VERSION, "r");
	char version[1024];
	fgets(version, sizeof(version), file_version);
	char version_current[1024];
	tmp2.SetTo("");
	tmp2 << BUILD_NUMBER;
	strcpy(version_current, tmp2.String());
		if (atoi(version) > atoi(version_current))
		{
		FILE* url = fopen(SAVE_UPDATE_URL, "r");
		char mURLToNewFile[1024];
		fgets(mURLToNewFile, sizeof(mURLToNewFile), url);
	
			switch((new BAlert("BAlertUpdate", STR_A_NEW_VERSION_IS_AVAILABLE[INT_LANGUAGE],
						 STR_NO_NEVER[INT_LANGUAGE], STR_NO[INT_LANGUAGE], STR_YES[INT_LANGUAGE]))->Go())
			{
			//yes
			case 2:
			{
			BString tmp;
			tmp.SetTo("/boot/beos/apps/NetPositive ");
			tmp.Append(mURLToNewFile);
			system(tmp.String());
			break;
			}
			case 0:
			savefile.AddBool(path, SAVE_FILE_NAME, NAME_CHECK_FOR_UPDATES, false, true);
			break;
			}
		}
	}
}

//----------------------------------------------------------------
//Notification
int32
mApp::NotificationThread_static(void *data)
{
	mApp *_Notification = (mApp *)data;
	_Notification->NotificationThread();
	return 0;
}

//----------------------------------------------------------------
void mApp::NotificationThread()
{
BString FileName;
BString FolderPath;
BString FilePath;
BPath Path;
BString tmpString;
BString tmpString2;
BString tmpString3;
MSave Save("Save");
int TodayMinute;
int TodayHour;
int NowMinute;
int NowHour;
time_t tmptodaytime;
struct tm *TodayTime;
BString Output;
BEntry Entry("/boot/home");
	while(RunNotification)
	{
	_mWindow->Lock();
	tmpString.SetTo("");
	tmpString << _mWindow->_CalenderView->mCalender->ThisDay();
	tmpString << "-";
	tmpString << _mWindow->_CalenderView->mCalender->ThisMonth();
	tmpString << _mWindow->_CalenderView->mCalender->ThisYear();
	_mWindow->Unlock();
	
	find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
	FolderPath.SetTo(Path.Path());
	FolderPath << SAVE_NOTE_PATH;
		for (int a = 1; a <= INT_MAXFILES; a++)
		{
		Path.SetTo(FolderPath.String());
		FileName.SetTo(tmpString.String());
		FileName << "-" << a;
		Path.Append(FileName.String());
		Entry.SetTo(Path.Path());
			if (Entry.Exists())
			{
			Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_TYPE, &tmpString2, "M_ERROR");
			Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_NOTIFY, &tmpString3, "M_ERROR");
				if (!strcmp(tmpString2.String(), "Apointment") && !strcmp(tmpString3.String(), "true"))
				{
				time(&tmptodaytime);
				TodayTime = localtime(&tmptodaytime);
				TodayMinute = TodayTime->tm_min;
				TodayHour   = TodayTime->tm_hour;
				
				Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_TIME, &tmpString2, "M_ERROR");
				tmpString2.Remove(tmpString2.FindFirst(":"), tmpString2.CountChars() - tmpString2.FindFirst(":"));
				NowHour = atoi(tmpString2.String());
				
				Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_TIME, &tmpString2, "M_ERROR");
				tmpString2.Remove(0, tmpString2.FindFirst(":") + 1);	
				NowMinute = atoi(tmpString2.String());
					if (NowMinute == TodayMinute && NowHour == TodayHour)
					{
					Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_TITLE, &tmpString2, "M_ERROR");
					Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_NOTE, &tmpString3, "M_ERROR");
					Output.SetTo(tmpString2.String());
					Output << "\n\n" << tmpString3.String();
					MPostit * mPostIt = new  MPostit(tmpString2.String(), Output.String(), STR_OK[INT_LANGUAGE]);
					mPostIt->Go();
					Save.AddString(FolderPath.String(), FileName.String(), SAVE_FILE_NOTIFY, "false", true);
					}
				}
				else if (!strcmp(tmpString2.String(), "Script") && !strcmp(tmpString3.String(), "true"))
				{
				time(&tmptodaytime);
				TodayTime = localtime(&tmptodaytime);
				TodayMinute = TodayTime->tm_min;
				TodayHour   = TodayTime->tm_hour;
								Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_TIME, &tmpString2, "M_ERROR");
				tmpString2.Remove(tmpString2.FindFirst(":"), tmpString2.CountChars() - tmpString2.FindFirst(":"));
				NowHour = atoi(tmpString2.String());
								Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_TIME, &tmpString2, "M_ERROR");
				tmpString2.Remove(0, tmpString2.FindFirst(":") + 1);	
				NowMinute = atoi(tmpString2.String());
					if (NowMinute == TodayMinute && NowHour == TodayHour)
					{
					Save.FindString(FolderPath.String(), FileName.String(), SAVE_FILE_NOTE, &tmpString, "M_ERROR");
					find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
					FolderPath.SetTo(Path.Path());
					FolderPath << SAVE_PATH_PART_1 << SAVE_PATH_PART_2;
					FileName.SetTo("TempRunScript");
					FilePath.SetTo("");
					FilePath << FolderPath.String() << FileName.String();
					tmpString2.SetTo("chmod 666 ");
					tmpString2 << FilePath.String();
					//Save
					system(tmpString2.String());
					FILE* file = fopen(FilePath.String(), "w");
					fprintf(file, tmpString.String());
					fclose(file);
					tmpString2.SetTo("chmod 755 ");
					tmpString2 << FilePath.String();
					system(tmpString2.String());
					//Run
					system(FilePath.String());
					Save.AddString(FolderPath.String(), FileName.String(), SAVE_FILE_NOTIFY, "false", true);
					}
				}
			}
		//Add more
		}
	sleep(59);
	}
}

