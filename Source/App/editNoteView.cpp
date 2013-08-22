//-----------------------  Local includes  ----------------------
#include "editNoteView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

//---------------------------------------------------------------
EditNoteView::EditNoteView(BRect frame, const char *name, uint32 resizeMask, uint32 flags, const char* title, const char* note)
		: BView(frame, name, resizeMask, flags)
{
SetViewColor(BeBack);

mTitleControl = new BTextControl(BRect(5, 10, 280, 40), "mTitleControl", STR_NOTE_NAME[INT_LANGUAGE], title, new BMessage(MSG_BOGUS));
mTitleControl->SetDivider(70);
mTextView = new BTextView(BRect(5, 40, frame.right - (5 + B_V_SCROLL_BAR_WIDTH), frame.bottom - 40), "mTextView", BRect(2, 2, frame.right - (12 + B_V_SCROLL_BAR_WIDTH), frame.bottom - 92), B_FOLLOW_LEFT);
mSaveButton = new BButton(BRect(frame.right - 120, frame.bottom - 30, frame.right - 20, frame.bottom - 10), "mSaveButton", STR_SAVE[INT_LANGUAGE], new BMessage(MSG_SAVE_NOTE));
mCancelButton = new BButton(BRect(frame.right - 230, frame.bottom - 30, frame.right - 130, frame.bottom - 10), "mCancelButton", STR_CANCEL[INT_LANGUAGE], new BMessage(MSG_CANCEL));
mTextView->SetText(note);
mTextView->MakeEditable(true);
mTextView->MakeSelectable(true);
mTextView->SetWordWrap(true);
mTextView->ForceFontAliasing(true);

AddChild(mScrollView = new BScrollView("scroll_view", mTextView, B_FOLLOW_ALL_SIDES, 0, false, true, B_FANCY_BORDER));
AddChild(mTitleControl);
AddChild(mSaveButton);
AddChild(mCancelButton);
}

//---------------------------------------------------------------
EditNoteView::~EditNoteView()
{

}

//---------------------------------------------------------------
void EditNoteView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}


//---------------------------------------------------------------
void EditNoteView::Draw(BRect update)
{

}


