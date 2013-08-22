//-----------------------  Local includes  ----------------------
#include "noteListView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------

// Local Defines ---------------------------------------------------------------
const rgb_color Back = (ui_color(B_PANEL_BACKGROUND_COLOR));

//---------------------------------------------------------------
NoteListView::NoteListView(BRect frame, const char *name, uint32 resizeMask, uint32 flags)
		: BView(frame, name, resizeMask, flags)
{
SetViewColor(Back);

mNoteListView = new BListView(BRect(10, 55, /*Bounds().right - (Bounds().left + 5)*/ Bounds().right - 25, Bounds().bottom - (90 + Bounds().top)), "mNoteListView",
				 B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL, B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS);
mNoteListView->SetSelectionMessage(new BMessage(MSG_NEW_ITEM_SELECTED));
AddChild(mScrollView = new BScrollView("scroll_view", mNoteListView, B_FOLLOW_ALL_SIDES, 0, false, true, B_FANCY_BORDER));

mAddButton = new BButton(BRect(20, Bounds().bottom - (80 + Bounds().top), 140, Bounds().bottom - (60 + Bounds().top)), "mAddButton", STR_ADD[INT_LANGUAGE],
				 new BMessage(MSG_ADD_SOMETHING), B_FOLLOW_BOTTOM | B_FOLLOW_LEFT , B_FRAME_EVENTS | B_WILL_DRAW | B_NAVIGABLE);

mEditButton = new BButton(BRect(20, Bounds().bottom - (55 + Bounds().top), 140, Bounds().bottom - (35 + Bounds().top)), "mEditButton", STR_EDIT[INT_LANGUAGE],
				 new BMessage(MSG_EDIT_SOMETHING), B_FOLLOW_BOTTOM | B_FOLLOW_LEFT , B_FRAME_EVENTS | B_WILL_DRAW | B_NAVIGABLE);
			
mRemoveButton = new BButton(BRect(20,Bounds().bottom - (30 + Bounds().top), 140, Bounds().bottom - (10 + Bounds().top)), "mRemoveButton", STR_REMOVE[INT_LANGUAGE],
				 new BMessage(MSG_REMOVE_SOMETHING), B_FOLLOW_BOTTOM | B_FOLLOW_LEFT , B_FRAME_EVENTS | B_WILL_DRAW | B_NAVIGABLE);

//AddChild(mNoteListView);
AddChild(mAddButton);
AddChild(mEditButton);
AddChild(mRemoveButton);
}

//---------------------------------------------------------------
NoteListView::~NoteListView()
{

}

//---------------------------------------------------------------
void NoteListView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	case B_VALUE_CHANGED:

	break;
	default:
	
	break;
	}
}

//---------------------------------------------------------------
void NoteListView::Draw(BRect update)
{

}

//---------------------------------------------------------------
void NoteListView::FrameResized(float width, float height)
{
//mScrollView->ResizeTo(width - 20, height - 150);
}

//---------------------------------------------------------------
void NoteListView::MouseDown(BPoint Where)
{/*
cout << "1_1337" << endl;
	if (fLastMousePoint.x == Where.x && fLastMousePoint.y == Where.y)
	{
	cout << "2_1337" << endl;
	BMessage* msg = Window()->CurrentMessage();
    int32 clicks = msg->FindInt32("clicks");
    int32 button = msg->FindInt32("buttons");
    	if (clicks == 2 && button == fLastButton)
    	{
    	cout << "3_1337" << endl;
    	Window()->PostMessage(MSG_EDIT_SOMETHING);
    	}
	}
fLastMousePoint.Set(Where.x, Where.y);
BMessage* msg = Window()->CurrentMessage();
int32 button = msg->FindInt32("buttons");
fLastButton = button;
*/
}

//---------------------------------------------------------------
void NoteListView::AddStringItem(const char* title, int level, bool expanded)
{
mNoteListView->AddItem(new BStringItem(title, level), expanded);
}

