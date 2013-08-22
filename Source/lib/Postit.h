#ifndef _Postit_h_
#define _Postit_h_

#include <InterfaceKit.h>
#include <AppKit.h>
#include <StorageKit.h>
#include <SupportKit.h>
#include <TranslationKit.h>
#include <iostream.h>

#define MSG_BUTTON1		'1001'
#define MSG_BUTTON2		'1002'
#define MSG_BUTTON3		'1003'

class MPostit : public BWindow	
{
public:
									 
							MPostit(const char* name, 
									const char* text, 
									const char* button1_text,
									const char* button2_text = NULL, 
									const char* button3_text = NULL);
									
	virtual					~MPostit();
	
	void					Go();
	
	virtual void 			MessageReceived(BMessage *message);
	
	const char*				Return(const char* return_text);
	
private:
	
	void					_CenterWindow(int window_width, int window_height);
	
	BTextView			*	PostTextView;
	BButton				*	PostButton1;
	BButton				*	PostButton2;
	BButton				*	PostButton3;
	BView				*	ButtonView;

	BString					Post_Name;
	BString					Post_Text;
	BString					Button1_Text;
	BString					Button2_Text;
	BString					Button3_Text;
	
	int						fWindowWidth, fWindowHeight;
	int						fIconNumber;
	bool					fButton2Enabled, fButton3Enabled;
	BRect					TempFrame;
};

#endif
