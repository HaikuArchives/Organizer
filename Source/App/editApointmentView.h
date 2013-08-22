#ifndef _editApointmentView_h_
#define _editApointmentView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class EditApointmentView
		: public BView
{
public:
							EditApointmentView(BRect frame, const char *name, uint32 resizeMask, uint32 flags, const char* title = "MyApointment", const char* time = "12:00", const char* note = "", bool notify = true);
							~EditApointmentView();
	virtual void			MessageReceived(BMessage *message);
	void					Draw(BRect update);
	void					CheckNotify();
	
	BTextControl		*	mTitleControl;
	BMenu				*	mHourMenu;
	BMenu				*	mMinuteMenu;
	BMenuField			*	mHourMenuField;
	BMenuField			*	mMinuteMenuField;
	BMenuItem			*	mMenuItem;
	BTextView			*	mTextView;
	BScrollView			*	mScriptScrollView;
	BButton				*	mSaveButton;
	BButton				*	mCancelButton;
	BCheckBox			*	mNotifyBox;
	
	
private:
	BString					tmpString, tmpString2, tmpString3;
private:

};

#endif

