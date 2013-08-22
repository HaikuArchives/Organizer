#ifndef _editNoteView_h_
#define _editNoteView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class EditNoteView
		: public BView
{
public:
							EditNoteView(BRect frame,
										 const char *name,
										 uint32 resizeMask,
										 uint32 flags,
										 const char* title = "MyTitle",
										 const char* note = "");
							~EditNoteView();
	virtual void			MessageReceived(BMessage *message);
	void					Draw(BRect update);
	
	BTextControl		*	mTitleControl;
	BTextView			*	mTextView;
	BButton				*	mSaveButton;
	BButton				*	mCancelButton;
	BScrollView			*	mScrollView;
private:

};

#endif

