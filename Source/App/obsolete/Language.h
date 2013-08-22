#ifndef _mWindow_h_
#define _mWindow_h_

//-----------------------  Local includes  ----------------------
#include "menuView.h"
#include "calenderView.h"
#include "navigateDateView.h"
#include "noteListView.h"
#include "Constants.h"

//----------------------- Global includes  ---------------------


class mWindow
		 : public BWindow
{
public:
							mWindow();
							~mWindow();
	virtual void			MessageReceived(BMessage *message);
	virtual bool			QuitRequested();
	void					RightClickMenu(int32 mDayOfMouseClick, 
											int32 mMonthOfMouseClick, 
											int32 mYearOfMouseClick);

	void					ApplyTheme();
	void					LoadSettings();
	void					SaveQuitSettings();
	
	void					SetSettingsPath(BPath *path);
private:
	
	NavigateDateView	*	_NavigateDateView;
	MenuView			*	_MenuView;
	CalenderView		*	_CalenderView;
	NoteListView		*	_NoteListView;

	BPopUpMenu			*	mRCPopUpMenu;
	BMenu				*	mRCMenu;
	BMenuItem			*	mRCMenuItem;

	BString 				fMouseButtonClicked;
	BString					tmpString;
	int						tmpInt;
	BRect					tmpRect;
	BPath					fPath;
	int32					fDayOfMouseClick;
	int32					fMonthOfMouseClick;
	int32					fYearOfMouseClick;
	int						fLanguage;
	int						fTheme;
	
//	BMenuItem *item;
};

#endif
