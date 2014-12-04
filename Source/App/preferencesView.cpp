//-----------------------  Local includes  ----------------------
#include "preferencesView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

//---------------------------------------------------------------
PreferencesView::PreferencesView(BRect frame, const char *name, uint32 resizeMask, uint32 flags)
		: BView(frame, name, resizeMask, flags)
{
//Set it up
SetViewColor(BeBack);

mCalenderStyleCheckBox = new BCheckBox(BRect(5, 15, 150, 30), "mCalenderStyleCheckBox", STR_AMERICAN_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER_STYLE));
//mCalenderStyleCheckBox->SetDivider(100);
mCalenderColorCheckBox = new BCheckBox(BRect(5, 35, 150, 50), "mCalenderColorCheckBox", STR_COLORFUL_CALENDER[INT_LANGUAGE], new BMessage(MSG_CALENDER_COLORFUL));
//mCalenderColorCheckBox->SetDivider(100);
mAutoUpdateCheckBox = new BCheckBox(BRect(5, 15, 250, 30), "mAutoUpdateCheckBox", STR_AUTOUPDATE[INT_LANGUAGE], new BMessage(MSG_AUTOUPDATE));

mLanguageMenu = new BMenu("mLanguageMenu");
	for (int a = 0; a < 5; a++)
	{
	mLanguageMenuItem = new BMenuItem(STR_LANGUAGES[a], new BMessage(MSG_LANGUAGE_CHANGED));
	mLanguageMenu->AddItem(mLanguageMenuItem);
	}
mLanguageMenu->SetLabelFromMarked(true);
mLanguageMenu->ItemAt(INT_LANGUAGE)->SetMarked(true);
	
mLanguageMenuField = new BMenuField(BRect(20, 20, 150, 40), "mLanguageMenuField", STR_LANGUAGE[INT_LANGUAGE], mLanguageMenu);

mLanguageBox = new BBox(BRect(5, 85, Bounds().right - 5, 130), "mLanguageBox");
mLanguageBox->SetLabel(STR_LANGUAGE[INT_LANGUAGE]);

mStyleBox = new BBox(BRect(5, 5, Bounds().right - 5, 80), "mStyleBox");
mStyleBox->SetLabel(STR_STYLE[INT_LANGUAGE]);

mSettingsBox = new BBox(BRect(5, 135, Bounds().right - 5, 240), "mSettingsBox");
mSettingsBox->SetLabel(STR_OTHER_SETTINGS[INT_LANGUAGE]);

mStyleBox->AddChild(mCalenderStyleCheckBox);
mStyleBox->AddChild(mCalenderColorCheckBox);
mLanguageBox->AddChild(mLanguageMenuField);
mSettingsBox->AddChild(mAutoUpdateCheckBox);
AddChild(mLanguageBox);
AddChild(mStyleBox);
AddChild(mSettingsBox);

MSave load("load");

find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
String.SetTo(Path.Path());
String.Append(SAVE_SETTINGS_PATH);
Path.SetTo(String.String());

load.FindBool(Path, SAVE_FILE_NAME, NAME_CALENDER_STYLE, &Bool, false);
mCalenderStyleCheckBox->SetValue(Bool);
load.FindBool(Path, SAVE_FILE_NAME, NAME_CALENDER_COLORFUL, &Bool, true);
mCalenderColorCheckBox->SetValue(Bool);
load.FindBool(Path, SAVE_FILE_NAME, NAME_CHECK_FOR_UPDATES, &Bool, true);
mAutoUpdateCheckBox->SetValue(Bool);
}

//---------------------------------------------------------------
PreferencesView::~PreferencesView()
{

}

//---------------------------------------------------------------
void PreferencesView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}


//---------------------------------------------------------------
void PreferencesView::Draw(BRect update)
{

}


