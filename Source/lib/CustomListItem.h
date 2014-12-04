#ifndef _CustomListItem_h_
#define _CustomListItem_h_

#define M_DOUBLE_CLICK		'1337'

//-----------------------  Local includes  ----------------------
#include <InterfaceKit.h>
#include <AppKit.h>
#include <StorageKit.h>
#include <SupportKit.h>
#include <TranslationKit.h>
#include <iostream>

//----------------------- Global includes  ----------------------

class MCustomListItem
		 : public BListItem
{
public:
						MCustomListItem(const char* title, const char* list_type);
						~MCustomListItem();
	
	void 				DrawItem(BView *owner, BRect frame, bool complete);
	const char*			Type();
	const char*			Title();
//	void				MouseDown(BPoint Where);
	
private:
	BString				fTitle;
	BString				fType;
	
	BPoint				fLastMouseClick;
};

#endif
