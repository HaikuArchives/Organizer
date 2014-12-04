#ifndef _Alert_h_
#define _Alert_h_

#include <InterfaceKit.h>
#include <AppKit.h>
#include <StorageKit.h>
#include <SupportKit.h>
#include <TranslationKit.h>
#include <iostream>

#define MSG_BUTTON1		'1001'
#define MSG_BUTTON2		'1002'
#define MSG_BUTTON3		'1003'

enum icon_type
{
M_QUESTION = 0,
M_INFO = 1,
M_EXPRESSION = 2,
M_IDEA = 3,
M_WARNING = 4
};

class MAlert : public BWindow	
{
public:
									 
							MAlert(const char* name, 
									const char* text, 
									const char* button1_text,
									const char* button2_text = NULL, 
									const char* button3_text = NULL, 
									bool post_its_look = false,
									icon_type icon = M_INFO);
	virtual					~MAlert();
	
	void					Go();
						
	void					SetText(const char* text);
	
	const char*				Text();
	
private:
	
	void					_SetupEverything();
	void					_CenterWindow(int window_width, int window_height);
	
	BTextView			*	AlertTextView;
	BButton				*	AlertButton1;
	BButton				*	AlertButton2;
	BButton				*	AlertButton3;
	BView				*	ButtonView;

	BString					Alert_Name;
	BString					Alert_Text;
	BString					Button1_Text;
	BString					Button2_Text;
	BString					Button3_Text;
	
	int						fWindowWidth, fWindowHeight;
	int						fIconNumber;
	bool					fPostItsLook, fButton2Enabled, fButton3Enabled;
	BRect					TempFrame;
};

#endif
