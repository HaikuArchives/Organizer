#ifndef _exportWindow_h_
#define _exportWindow_h_

//-----------------------  Local includes  ----------------------
#include "exportView.h"
#include "Constants.h"

//----------------------- Global includes  ----------------------


class ExportWindow
		 : public BWindow
{
public:
						ExportWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags, int Month, int Year);
						~ExportWindow();
	virtual void		MessageReceived(BMessage *message);
	virtual bool		QuitRequested();
	
	BString				fSaveTo;

private:
	ExportView		*	_ExportView;
	
	int 				fMonth;
	int					fYear;
	int 				fDay;
	bool				fFirstNoteOfTheDay;
	bool				fIncludeNotes;
	bool				fIncludeApointments;

	BString				fContent;
	BString				tmpString;
	
	BString				fType;
	BString				fTitle;
	BString				fNote;
	BString				fTime;	
	
	BString				TableBGColor1;
	BString				TableBGColor2;
	BString				TableColor;

	void				Head();
	void				Title();
	void				Body();
	void				MainLoop();
	void				End();
};

#endif
