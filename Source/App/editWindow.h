#ifndef _editWindow_h_
#define _editWindow_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"
#include "editNoteView.h"
#include "editScriptView.h"
#include "editApointmentView.h"

//----------------------- Global includes  ----------------------


class EditWindow
		 : public BWindow
{
public:
							EditWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags);
							~EditWindow();
	virtual void			MessageReceived(BMessage *message);
	virtual bool			QuitRequested();
	void					SaveNote();
	void					SaveScript();
	void					SaveApointment();

private:
	EditNoteView		*	_EditNoteView;
	EditScriptView		*	_EditScriptView;
	EditApointmentView	*	_EditApointmentView;
	
	BRect					fFrame;
	BPath					Path;
		
	BString					fSaveStuff;
	BString					fFileName;
	BString					fCalcPath;
	
	BString					tmpString;
	BString					tmpString2;
	
	BString 				fType;
	BString 				fTitle;
	BString 				fTime;
	BString 				fNote;
	BString 				fPath;
	BString	 				fNotify;
	int32					fYear, fMonth, fDay;

};

#endif
