//-----------------------  Local includes  ----------------------
#include "exportView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------


//---------------------------------------------------------------
ExportView::ExportView(BRect frame, const char *name, uint32 resizeMask, uint32 flags, int Month, int Year)
		: BView(frame, name, resizeMask, flags)
{
SetViewColor(BeBack);

fMonth = Month;
fYear = Year;

mNoteCheckBox = new BCheckBox(BRect(5, 15, 200, 30), "mNoteCheckBox", STR_INCLUDE_NOTE[INT_LANGUAGE], new BMessage(MSG_BOGUS));
mNoteCheckBox->SetValue(true);
mApointmentCheckBox = new BCheckBox(BRect(5, 35, 200, 50), "mApointmentCheckBox", STR_INCLUDE_APOINTMENT[INT_LANGUAGE], new BMessage(MSG_BOGUS));
mApointmentCheckBox->SetValue(true);
mExportButton = new BButton(BRect(frame.right - 100, frame.bottom - 30, frame.right - 10, frame.bottom - 10), "mExportButton", STR_EXPORT[INT_LANGUAGE], new BMessage(MSG_EXPORT));
mBrowseButton = new BButton(BRect(5, 60, 100, 80), "mBrowseButton", STR_EXPORT_TO[INT_LANGUAGE], new BMessage(MSG_EXPORT_HTML_FILE));
mFileNameControl = new BTextControl(BRect(5, 90, 160, 110), "mFileNameControl", STR_FILENAME[INT_LANGUAGE], "index.html", new BMessage(MSG_BOGUS));
mFileNameControl->SetModificationMessage(new BMessage(MSG_EXPORT_FILENAME_CHANGED));

mSettingsBox = new BBox(BRect(5, 5, frame.right - 5, frame.bottom - 60), "mSettingsBox");
mSettingsBox->SetLabel(STR_SETTINGS[INT_LANGUAGE]);

//Localization
GetFont(&fFont);

//mExportButton
tmpInt = fFont.StringWidth(mExportButton->Label());
tmpInt += 20;
mExportButton->ResizeTo(tmpInt, 25);
mExportButton->MoveTo(frame.right - (tmpInt + 15), frame.bottom - (25 + 15));
//mBrowseButton
tmpInt = fFont.StringWidth(mBrowseButton->Label());
tmpInt += 20;
mBrowseButton->ResizeTo(tmpInt, 25);
//mFileNameControl
tmpInt = fFont.StringWidth(mFileNameControl->Label());
tmpInt += 5;
mFileNameControl->SetDivider(tmpInt);

mSettingsBox->AddChild(mNoteCheckBox);
mSettingsBox->AddChild(mApointmentCheckBox);
mSettingsBox->AddChild(mBrowseButton);
mSettingsBox->AddChild(mFileNameControl);
AddChild(mExportButton);
AddChild(mSettingsBox);
}

//---------------------------------------------------------------
ExportView::~ExportView()
{

}

//---------------------------------------------------------------
void ExportView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}


//---------------------------------------------------------------
void ExportView::Draw(BRect update)
{

}

