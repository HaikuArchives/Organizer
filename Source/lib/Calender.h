#ifndef _CALENDER_H_
#define _CALENDER_H_

// Standard Includes -----------------------------------------------------------

// System Includes -------------------------------------------------------------
#include <InterfaceKit.h>
#include <AppKit.h>
#include <StorageKit.h>
#include <SupportKit.h>
#include <TranslationKit.h>
#include <iostream.h>

// Project Includes ------------------------------------------------------------

// Local Includes --------------------------------------------------------------

// Local Defines ---------------------------------------------------------------

enum calender_language {
M_ENGLISH = 0,
M_NORWEGIAN = 1,
M_SPANISH = 2,
M_GERMAN = 3,
M_GENERIC = 4
};

// Globals ---------------------------------------------------------------------

// MCalender class ---------------------------------------------------------------
class MCalender : public BControl {
public:
							MCalender(BRect frame,
									const char *name,
									const char *label,
									BMessage *message,
									int32 year,
									int32 month_number,
									int32 day,
									bool calenderstyle_colorful = true,
									bool american_style_calender = false,
									calender_language language = M_ENGLISH,
									uint32 resizingMode = B_FOLLOW_LEFT |
														B_FOLLOW_TOP,
									uint32 flags = B_NAVIGABLE | B_WILL_DRAW |
														B_FRAME_EVENTS);

virtual						~MCalender();

//							MCalender(BMessage *data);

virtual void				MessageReceived(BMessage *msg);
virtual void 				FrameMoved(BPoint new_position);
virtual void				FrameResized(float w,float h);
virtual void 				KeyDown(const char * bytes, int32 n);
virtual void 				MouseDown(BPoint point);
virtual void 				MouseUp(BPoint pt);
virtual void 				MouseMoved(BPoint pt, uint32 c, const BMessage *m);

virtual void				Update();
virtual void				Draw(BRect frame);
virtual void				DrawBox(BRect box, int day_number, int box_number);
virtual void				DrawDate(BRect box, int day_number, int box_number);
virtual void				DrawDayName(BRect box, int day_number, int box_number);
virtual void				SetYear(int32 year);
int32						Year();
virtual void				SetMonth(int32 month_number);
int32						Month();
virtual void				SetDay(int32 day);
int32						Day();
virtual void				SetWhen(int32 year, int32 month_number, int32 day);
virtual void				SetBoxWidthAndHeight(int height, int width);
virtual void				SetAmericanStyleCalender(bool style);
bool						AmericanStyleCalender();
virtual void				SetColorfulCalender(bool colorful);
bool						ColorfulCalender();
void						SetBackgroundColor(rgb_color color);
rgb_color					BackgroundColor();

int32						ThisYear();
int32						ThisMonth();
int32						ThisDay();

int							BoxHeight();
int							BoxWidth();

private:

void						_SetBoxBounds();
void 						_IsTheDaysToday(BRect frame, rgb_color color, int day);

BRect						fFrame;
BRect						fBox[8][7];
int32						fYear;
int32						fMonthNumber;
int32						fDayNumber;
int							fDayNumberOfBeginningOfMonth;
int							fDate;
bool						fCalenderIsAmericaStyle;
bool						fCalenderStyleIsColorful;
int 						DaysInTheMonth[13];
int 						fBoxWidth;
int 						fBoxHeight;
int							fLanguageNumber;
BRect						fDaySelectedBox;
BRect						fDayOldSelectedBox;
rgb_color					fBackgroundColor;
bool						fRedrawBackground;

BString						tmp4;
int							tmp;
int							tmp2;
int							tmp3;
bool						tmpbool;

long						Time;
struct tm					*TodayTime;

BString						fMonthName;
BString						fDayName;
BString						fDayNumberString;

};

#endif