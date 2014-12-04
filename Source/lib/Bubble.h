#ifndef _Bubble_h_
#define _Bubble_h_

#include <InterfaceKit.h>
#include <AppKit.h>
#include <StorageKit.h>
#include <SupportKit.h>
#include <TranslationKit.h>
#include <iostream>


class _EXPORT MBubble	
								: public BMessage	
{
public:
									MBubble(const char* name, const char* text);
	virtual					~MBubble();
	
	void					Hide();
						
	void					SetText(const char* text);
		
	void					Show();
	
	const char*				Text();
								
	rgb_color				High_Color;
	rgb_color				View_Color;	
	rgb_color				Low_Color;
	rgb_color				Black;
	rgb_color				White;
	BRect					Window_Rect;
	BString					Bubble_Text;
	float					left, top, right, bottom, width, height;
	
private:
	BPoint					MouseStrokeLocation;
	BWindow* 				BubbleWindow;
	BTextView* 				BubbleTextView;
	BView* 					BubbleView;
	BView* 					BubbleBGView;
	BPoint					Mouse_Location;
	font_height				fontheight;
};

#endif
