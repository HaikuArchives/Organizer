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
	
	void					GetSettingsPath(BPath *path);
	
	//A large function for gettings all the notes, apointments and scripts 
	void					GetNotes();
	void					GetPathToSelectedFile(BString* string);
	BString				TypeInFile(const char* path);
	BString				TimeInFile(const char* path);
	BString				NoteInFile(const char* path);
	BString				TitleInFile(const char* path);
	BString				NotifyInFile(const char* path);

	NavigateDateView	*	_NavigateDateView;
	MenuView			*	_MenuView;
	CalenderView		*	_CalenderView;
	NoteListView		*	_NoteListView;

private:

	BPopUpMenu			*	mRCPopUpMenu;
	BMenu				*	mRCMenu;
	BMenuItem			*	mRCMenuItem;

	BString 				fMouseButtonClicked;
	BString					tmpString;
	BString					tmpString2;
	BString					tmpString3;
	BString					tmpString4;
	int						tmpInt;
	BRect					tmpRect;
	BPath					fPath;
	BFile					fFile;
	int32					fDayOfMouseClick;
	int32					fMonthOfMouseClick;
	int32					fYearOfMouseClick;
	int						fLanguage;
	int						fTheme;
//	BMenuItem *item;
};

#endif
