#ifndef _exportWindowView_h_
#define _exportWindowView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class ExportView
		: public BView
{
public:
						ExportView(BRect frame, const char *name, uint32 resizeMask, uint32 flags, int Month, int Year);
						~ExportView();
	virtual void		MessageReceived(BMessage *message);
	void				Draw(BRect update);
	
	BBox			*	mSettingsBox;
	BCheckBox		*	mNoteCheckBox;
	BCheckBox		*	mApointmentCheckBox;
	BButton			*	mExportButton;
	BButton			*	mBrowseButton;
	BTextControl	*	mFileNameControl;
	int 				fMonth;
	int					fYear;

private:
	BFont 				fFont;
	int32				tmpInt;
};

#endif

