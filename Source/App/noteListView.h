#ifndef _noteListView_h_
#define _noteListeView_h_

//-----------------------  Local includes  ----------------------
#include "Constants.h"

//----------------------- Global includes  ----------------------


class NoteListView
		: public BView
{
public:
							NoteListView(BRect frame, const char *name, uint32 resizeMask, uint32 flags);
							~NoteListView();
	virtual void			MessageReceived(BMessage *message);
	void					Draw(BRect update);
	virtual void			FrameResized(float width, float height);
	void					MouseDown(BPoint Where);
	void					AddStringItem(const char* title, int level, bool expanded);

	BButton				*	mAddButton;
	BButton				*	mEditButton;
	BButton				*	mRemoveButton;
	BListView			*	mNoteListView;
	BListItem			*	mNoteListItem;
	BScrollView			*	mScrollView;
private:
	BPoint					fLastMousePoint;
	int32					fLastButton;

};

#endif

