#ifndef _editScriptView_h_
#define _editScriptView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class EditScriptView
		: public BView
{
public:
							EditScriptView(BRect frame, const char *name, uint32 resizeMask, uint32 flags, const char* title = "MyScript", const char* time = "12:00", const char* note = "", bool notify = true);
							~EditScriptView();
	virtual void			MessageReceived(BMessage *message);
	void					Draw(BRect update);
	void					CheckNotify();
	void					History();
	void					GetPathOfSelectedFile(BString *StrPath);
	
	BTextControl		*	mTitleControl;
	BMenu				*	mHourMenu;
	BMenu				*	mMinuteMenu;
	BMenu				*	mHistoryMenu;
	BMenuField			*	mHourMenuField;
	BMenuField			*	mMinuteMenuField;
	BMenuField			*	mHistoryMenuField;
	BMenuItem			*	mMenuItem;
	BTextView			*	mTextView;
	BScrollView			*	mScriptScrollView;
	BButton				*	mSaveButton;
	BButton				*	mCancelButton;
	BCheckBox			*	mRunScriptBox;
	
private:
	BString					tmpString, tmpString2, tmpString3;
};

#endif

