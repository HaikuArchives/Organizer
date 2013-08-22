#ifndef _preferencesView_h_
#define _preferencesView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class PreferencesView
		: public BView
{
public:
							PreferencesView(BRect frame, const char *name, uint32 resizeMask, uint32 flags);
							~PreferencesView();
	virtual void			MessageReceived(BMessage *message);
	void					Draw(BRect update);
	
	BMenu				*	mLanguageMenu;
	BMenuItem			*	mLanguageMenuItem;
	BMenuField			*	mLanguageMenuField;
	BCheckBox			*	mCalenderStyleCheckBox;
	BCheckBox			*	mCalenderColorCheckBox;
	BCheckBox			*	mAutoUpdateCheckBox;;
	BBox				*	mLanguageBox;
	BBox				*	mStyleBox;
	BBox				*	mSettingsBox;
	
private:
	BPath 				Path;
	BString 			String;
	bool				Bool;

};

#endif

