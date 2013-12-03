//-----------------------  Local includes  ----------------------
#include "preferencesWindow.h"

//----------------------- Global includes  ----------------------


//---------------------------------------------------------------
PreferencesWindow::PreferencesWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags)
			 : BWindow(frame, title, B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL, B_NOT_RESIZABLE)
{
_PreferencesView = new PreferencesView(Bounds(), "_PreferencesView", B_FOLLOW_ALL, B_WILL_DRAW | B_NAVIGABLE);

AddChild(_PreferencesView);
}

//---------------------------------------------------------------
PreferencesWindow::~PreferencesWindow()
{

}

//---------------------------------------------------------------
void PreferencesWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	case MSG_CALENDER_STYLE:
		be_app->PostMessage(MSG_CALENDER_STYLE);
	break;
	case MSG_CALENDER_COLORFUL:
		be_app->PostMessage(MSG_CALENDER_COLORFUL);
	break;
	case MSG_LANGUAGE_CHANGED:
		be_app->PostMessage(MSG_LANGUAGE_CHANGED);
	break;
	case MSG_AUTOUPDATE:
	{
		MSave Save("Save");
		BPath Path;
		BString String;
		
		find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
		String.SetTo(Path.Path());
		String.Append(SAVE_SETTINGS_PATH);
		String.Append(SAVE_FILE_NAME);
		Save.AddBool(String.String(), NAME_CHECK_FOR_UPDATES, _PreferencesView->mAutoUpdateCheckBox->Value(), true);
	break;
	}
	default:
	
	break;
	}
}

//---------------------------------------------------------------
bool PreferencesWindow::QuitRequested()
{
	Close();
}


