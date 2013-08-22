//-----------------------  Local includes  ----------------------
#include "editApointmentView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

//---------------------------------------------------------------
EditApointmentView::EditApointmentView(BRect frame, const char *name, uint32 resizeMask, uint32 flags,
				 const char* title = "MyApointment", const char* time = "12:00", const char* note = "",
				 bool notify = true)
		: BView(frame, name, resizeMask, flags)
{
//Set it up
SetViewColor(BeBack);

//Construct
mTitleControl = new BTextControl(BRect(5, 5, 240, 35), "mTitleControl", STR_APOINTMENT_NAME[INT_LANGUAGE], "MyScript",
					 new BMessage(MSG_BOGUS), B_FOLLOW_LEFT | B_FOLLOW_TOP);
mTitleControl->SetDivider(90);
mTitleControl->SetText(title);

mHourMenu = new BMenu("mHourMenu");
mHourMenu->SetLabelFromMarked(true);

mMinuteMenu = new BMenu("mMinuteMenu");
mMinuteMenu->SetLabelFromMarked(true); 

mHourMenuField = new BMenuField(BRect(260, 5, 370, 25), "mHourMenuField",  STR_NOTIFY_ME_AT[INT_LANGUAGE],
					mHourMenu,  B_FOLLOW_LEFT | B_FOLLOW_TOP);
mHourMenuField->SetDivider(70);

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

mNotifyBox = new BCheckBox(BRect(260, 30, 330, 45), "mNotifyBox", STR_NOTIFY_ME[INT_LANGUAGE], new BMessage(MSG_NOTIFY_APOINTMENT_CHECKBOX));
mNotifyBox->SetValue(notify);

mSaveButton = new BButton(BRect(frame.right - 120, frame.bottom - 30, frame.right - 20, frame.bottom - 10), "mSaveButton", STR_SAVE[INT_LANGUAGE], new BMessage(MSG_SAVE_APOINTMENT));
mCancelButton = new BButton(BRect(frame.right - 230, frame.bottom - 30, frame.right - 130, frame.bottom - 10), "mCancelButton", STR_CANCEL[INT_LANGUAGE], new BMessage(MSG_CANCEL));


//Set up and add
tmpString2.SetTo(time);
tmpString2.Remove((tmpString2.FindFirst(":")), tmpString2.CountChars() - (tmpString2.FindFirst(":")));
	for (int a = 1; a <= 23; a++)
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
AddChild(mNotifyBox);
AddChild(mSaveButton);
AddChild(mCancelButton);

CheckNotify();
}

//---------------------------------------------------------------
EditApointmentView::~EditApointmentView()
{

}

//---------------------------------------------------------------
void EditApointmentView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}


//---------------------------------------------------------------
void EditApointmentView::Draw(BRect update)
{

}


//---------------------------------------------------------------
void EditApointmentView::CheckNotify()
{
	if (mNotifyBox->Value())
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
