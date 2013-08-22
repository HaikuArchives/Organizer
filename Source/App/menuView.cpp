//-----------------------  Local includes  ----------------------
#include "menuView.h"

//-----------------------  Global includes  ----------------------


//-----------------------  Local Variables  ----------------------
const BRect mMenuBarRect				(0, 0, 1600, 20);

//---------------------------------------------------------------
MenuView::MenuView(BRect frame, const char *name, uint32 resizeMask, uint32 flags)
		: BView(frame, name, resizeMask, flags)
{
mMenuBar = new BMenuBar(mMenuBarRect, "mMenuBar", B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP, 
						B_ITEMS_IN_ROW, true);
//File
mMenu = new BMenu(STR_FILE[INT_LANGUAGE]);
/*
mMenuItem = new BMenuItem("Load", new BMessage(MSG_ABOUT));
mMenu->AddItem(mMenuItem);

mMenu->AddSeparatorItem();
*/
mMenuItem = new BMenuItem(STR_EXPORT_HTML[INT_LANGUAGE], new BMessage(MSG_EXPORT_HTML), 'E', B_COMMAND_KEY);
mMenu->AddItem(mMenuItem);

mMenu->AddSeparatorItem();

mMenuItem = new BMenuItem(STR_QUIT[INT_LANGUAGE], new BMessage(MSG_QUIT), 'Q', B_COMMAND_KEY);
mMenu->AddItem(mMenuItem);

mMenuBar->AddItem(mMenu);
//Edit
mMenu = new BMenu(STR_EDIT[INT_LANGUAGE]);

mMenuItem = new BMenuItem(STR_PREFERENCES[INT_LANGUAGE], new BMessage(MSG_PREFERENCES), 'P', B_COMMAND_KEY);
mMenu->AddItem(mMenuItem);

mMenuBar->AddItem(mMenu);
//View
/*
mMenu = new BMenu(STR_VIEW[INT_LANGUAGE]);

mMenuItem = new BMenuItem(STR_ABOUT[INT_LANGUAGE], new BMessage(MSG_ABOUT));
mMenu->AddItem(mMenuItem);

mMenuItem = new BMenuItem("Themes", new BMessage(MSG_APPLY_THEME));
mMenu->AddItem(mMenuItem);

mMenuBar->AddItem(mMenu);
*/
//About
mMenu = new BMenu(STR_ABOUT[INT_LANGUAGE]);

mMenuItem = new BMenuItem(STR_ABOUT[INT_LANGUAGE], new BMessage(MSG_ABOUT), 'A', B_COMMAND_KEY);
mMenu->AddItem(mMenuItem);

mMenuBar->AddItem(mMenu);

AddChild(mMenuBar);

}

//---------------------------------------------------------------
MenuView::~MenuView()
{

}

//---------------------------------------------------------------
void MenuView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	default:
	
	break;
	}
}

//---------------------------------------------------------------
void MenuView::Draw(BRect update)
{

}

