/*
Warning, this code is one big hackjob and i will _NOT_ pay your insanity-hospital
bill.........
:-D
*/



// Standard Includes -----------------------------------------------------------

// System Includes -------------------------------------------------------------
#include "Calender.h"

// Project Includes ------------------------------------------------------------

// Local Includes --------------------------------------------------------------

// Local Defines ---------------------------------------------------------------
const rgb_color Red = 					{250,10, 10,	255};
const rgb_color White = 				{250,250,250,	255};
const rgb_color Black = 				{0,  0,  0,		255};
const rgb_color DarkerGray = 			{200,200,200,	255};
const rgb_color Gray = 					{219,219,219,	255};
const rgb_color LightGray = 			{230,230,230,	255};
const rgb_color LightRed = 				{226,116,102,	255};
const rgb_color DarkRed = 				{218,59, 14,	255};
const rgb_color LightBlue = 			{49, 182,219,	255};
const rgb_color LightGreen = 			{149,197,152,	255};
const rgb_color LightYellow = 			{225,216,138,	255};
const rgb_color DarkBlue = 				{38, 113,217,	255};
const rgb_color DarkGreen = 			{82, 186,73,	255};
const rgb_color DarkYellow = 			{244,204,66,	255};
const rgb_color LightPurple = 			{207,166,201,	255};
const rgb_color GrayBlue = 				{179,192,219,	255};
const rgb_color LightMetallicBlue =		{143,166,240,	255};
const rgb_color MedMetallicBlue =		{75, 96, 154,	255};
const rgb_color DarkMetallicBlue =		{78, 89, 126,	255};
const rgb_color PineAppleGreen =		{183,200,184,	255};
const rgb_color PineAppleYellow =		{254,248,224,	255};
const rgb_color PineAppleDarkGreen =	{163,180,164,	255};

//This code is non-america, so day1 = monday day7 = sunday
const char* Day1[12] = {"Monday", /*norwegian*/"Mandag", "Monday", "Monday", "Monday", "Monday", "Monday", "Monday", "Monday",
							"Monday", "Monday", "Monday"};
const char* Day2[12] = {"Tuesday", /*norwegian*/"Tirsdag", "Tuesday", "Tuesday", "Tuesday", "Tuesday", "Tuesday", "Tuesday", "Tuesday",
							"Tuesday", "Tuesday", "Tuesday"};
const char* Day3[12] = {"Wednesday", /*norwegian*/"Onsdag", "Wednesday", "Wednesday", "Wednesday", "Wednesday", "Wednesday", "Wednesday", "Wednesday",
							"Wednesday", "Wednesday", "Wednesday"};
const char* Day4[12] = {"Thursday", /*norwegian*/"Torsdag", "Thursday", "Thursday", "Thursday", "Thursday", "Thursday", "Thursday", "Thursday",
							"Thursday", "Thursday", "Thursday"};
const char* Day5[12] = {"Friday", /*norwegian*/"Fredag", "Friday", "Friday", "Friday", "Friday", "Friday", "Friday", "Friday",
							"Friday", "Friday", "Friday"};
const char* Day6[12] = {"Saturday", /*norwegian*/"Lørdag", "Saturday", "Saturday", "Saturday", "Saturday", "Saturday", "Saturday", "Saturday",
							"Saturday", "Saturday", "Saturday"};
const char* Day7[12] = {"Sunday", /*norwegian*/"Søndag", "Sunday", "Sunday", "Sunday", "Sunday", "Sunday", "Sunday", "Sunday",
							"Sunday", "Sunday", "Sunday"};	
int DaysInTheMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};			

// Globals ---------------------------------------------------------------------

//Class
MCalender::MCalender(BRect frame, const char *name, const char *label, BMessage *message, int32 year,
						int32 month_number, int32 day, bool calenderstyle_colorful, bool american_style_calender,
						calender_language language, uint32 resizingMode, uint32 flags)				
						:       BControl(frame, name, label, message, resizingMode, flags), 
				fFrame(frame), 
				fYear(year),
				fMonthNumber(month_number),
				fDayNumber(day),
				fCalenderStyleIsColorful(calenderstyle_colorful),
				fCalenderIsAmericaStyle(american_style_calender),
				//1st of january 2000 is a friday
				fDayNumberOfBeginningOfMonth(5)
{
fBoxWidth = 80;
fBoxHeight = 80;
fLanguageNumber = language;
fBackgroundColor.red = 216;
fBackgroundColor.green = 216;
fBackgroundColor.blue = 216;
fBackgroundColor.alpha = 255;
fRedrawBackground = true;

//Set the number of days in all the months
DaysInTheMonth[0] = 0;
DaysInTheMonth[1] = 31;
DaysInTheMonth[2] = 28;
DaysInTheMonth[3] = 31;
DaysInTheMonth[4] = 30;
DaysInTheMonth[5] = 31;
DaysInTheMonth[6] = 30;
DaysInTheMonth[7] = 31;
DaysInTheMonth[8] = 31;
DaysInTheMonth[9] = 30;
DaysInTheMonth[10] = 31;
DaysInTheMonth[11] = 30;
DaysInTheMonth[12] = 31;

SetViewColor(fBackgroundColor);
}

//-------------------------------------------------------------------------------
MCalender::~MCalender()
{

}

//-------------------------------------------------------------------------------
//MCalender::MCalender(BMessage *data)
//{

//}

//-------------------------------------------------------------------------------
void MCalender::MessageReceived(BMessage *msg)
{

}

//-------------------------------------------------------------------------------
void MCalender::FrameMoved(BPoint new_position)
{

}

//-------------------------------------------------------------------------------
void MCalender::FrameResized(float w, float h)
{

}

//--------------------------------------------------------------------------------
void MCalender::KeyDown(const char * bytes, int32 n)
{
//Add
}

//--------------------------------------------------------------------------------
void MCalender::MouseDown(BPoint point)
{
//Get info on what key it is
BMessage* msg = Window()->CurrentMessage();
int32 button = msg->FindInt32("buttons");

	tmp4.SetTo("PrimaryMouseButton");
	//SetWhatDayThatIsSelected
	//Bounds 1
	for (tmp = 1; tmp <= 7; tmp++)
	{	
		//Bounds2
		for (tmp2 = 1; tmp2 <= 6; tmp2++)
		{
			//if the mouse is there
			if (fBox[tmp][tmp2].left <= point.x && fBox[tmp][tmp2].right >= point.x && 
				fBox[tmp][tmp2].top <= point.y && fBox[tmp][tmp2].bottom >= point.y)
			{
			fDayOldSelectedBox.Set(fDaySelectedBox.left, fDaySelectedBox.top,
									fDaySelectedBox.right, fDaySelectedBox.bottom);
			fDaySelectedBox.Set(fBox[tmp][tmp2].left, fBox[tmp][tmp2].top, 
								fBox[tmp][tmp2].right, fBox[tmp][tmp2].bottom);
			
				//Only set new day if one of the days are pressed (presses outside the day's area is not counted because of this function)
				if ((tmp + (tmp2 * 7) - 7 - fDayNumberOfBeginningOfMonth) <= DaysInTheMonth[fMonthNumber] &&
					(tmp + (tmp2 * 7) - 7 - fDayNumberOfBeginningOfMonth) >= 1)
				{
				fDayNumber = (tmp + (tmp2 * 7) - 7 - fDayNumberOfBeginningOfMonth);
				
				
				
				}
			}
		}
	}
	//Add to message
	if (Message()->HasString("button") == true)
	{
	Message()->ReplaceString("button", tmp4.String());
	}
	else
	{
	Message()->AddString("button", tmp4.String());
	}
	if (button == B_SECONDARY_MOUSE_BUTTON)
	{
	tmp4.SetTo("SecondaryMouseButton");
		//Add to message
		if (Message()->HasString("button") == true)
		{
		Message()->ReplaceString("button", tmp4.String());
		}
		else
		{
		Message()->AddString("button", tmp4.String());
		}
	}

//Add day, month and year
	//Add to message
	tmp4.SetTo("");
	tmp4 << fDayNumber;
	if (Message()->HasString("day") == true)
	{
	Message()->ReplaceString("day", tmp4.String());
	}
	else
	{
	Message()->AddString("day", tmp4.String());
	}
	//Add to message
	tmp4.SetTo("");
	tmp4 << fMonthNumber;
	if (Message()->HasString("month") == true)
	{
	Message()->ReplaceString("month", tmp4.String());
	}
	else
	{
	Message()->AddString("month", tmp4.String());
	}
	//Add to message
	tmp4.SetTo("");
	tmp4 << fYear;
	if (Message()->HasString("year") == true)
	{
	Message()->ReplaceString("year", tmp4.String());
	}
	else
	{
	Message()->AddString("year", tmp4.String());
	}
	
Window()->PostMessage(Message());
Draw(fFrame);
}

//--------------------------------------------------------------------------------
void MCalender::MouseUp(BPoint pt)
{
//Add
}

//--------------------------------------------------------------------------------
void MCalender::MouseMoved(BPoint pt, uint32 c, const BMessage *m)
{
//Add
}

//-------------------------------------------------------------------------------
void MCalender::Update()
{
Draw(fFrame);
}

//-------------------------------------------------------------------------------
void MCalender::Draw(BRect frame)
{
//Set the bounds for all Box'es
_SetBoxBounds();
	if (fRedrawBackground)
	{
	SetHighColor(fBackgroundColor);
	FillRect(fFrame);
	fRedrawBackground = false;
	}

	//We dont take your false dates around here
	if (fYear < 2000 || fMonthNumber > 12 || fMonthNumber < 1 || fDayNumber > 31 || fDayNumber < 1)
	{
	std::cout << "Date doesnt exist" << std::endl;
	}
	//If American style, add one more day (they are stupid and begin the week with a sunday)
	if (fCalenderIsAmericaStyle)
	{
	fDayNumberOfBeginningOfMonth = 6;
	}
	else
	{
	fDayNumberOfBeginningOfMonth = 5;
	}
//every year dividable with 4 is a "skuddår" with 29days in february
	//Get day of the 1 of january in the correct year
	for (tmp = 2000; fYear > tmp ; tmp++)
	{
	tmp2 = (tmp / 4);
	//Set the number of days in february that year
		if (tmp2 * 4 == tmp)
		{
		fDayNumberOfBeginningOfMonth += 2;
		}
		else
		{
		fDayNumberOfBeginningOfMonth++;
		}
		//if it is more or equal to 7 days it should be moved a line up
		while (fDayNumberOfBeginningOfMonth >= 7)
		{
		fDayNumberOfBeginningOfMonth -= 7;
		}
	}
	//Set februrary to the right number of days days
	tmp2 = (fYear / 4);
		if (tmp2 * 4 == tmp)
		{
		DaysInTheMonth[2] = 29;
		}
		else
		{
		DaysInTheMonth[2] = 28;
		}
	//Get the correct first day of the correct month
	for (tmp = 1; tmp < fMonthNumber; tmp++)
	{
	tmp2 = DaysInTheMonth[tmp]  - 28;
	fDayNumberOfBeginningOfMonth += tmp2;
	
		if (fDayNumberOfBeginningOfMonth >= 7)
		{
		fDayNumberOfBeginningOfMonth -= 7;
		}
	}
	//Add all days to the calender
	for (tmp = 1; tmp <= DaysInTheMonth[fMonthNumber]; tmp++)
	{
	tmp2 = tmp + fDayNumberOfBeginningOfMonth;
	tmp3 = 1;
		while (tmp2 > 7)
		{
		//This is the function above (look beneath)
		tmp2 -= 7;
		tmp3 += 1;
		}
	DrawBox(fBox[tmp2][tmp3], tmp, tmp + fDayNumberOfBeginningOfMonth);
	}
}

//-------------------------------------------------------------------------------
void MCalender::DrawBox(BRect box, int day_number, int box_number)
{
	//Colourful?
	if (fCalenderStyleIsColorful)
	{
	//tmp2 here is the day (used by the function above))
		switch (tmp2)
		{
		case 1:
		SetHighColor(LightYellow);
		SetLowColor(LightYellow);
		break;
		case 2:
		SetHighColor(LightBlue);
		SetLowColor(LightBlue);
		break;
		case 3:
		SetHighColor(LightGreen);
		SetLowColor(LightGreen);
		break;
		case 4:
		SetHighColor(DarkYellow);
		SetLowColor(DarkYellow);
		break;
		case 5:
		SetHighColor(LightPurple);
		SetLowColor(LightPurple);
		break;
		case 6:
		SetHighColor(GrayBlue);
		SetLowColor(GrayBlue);
		break;
		case 7:
		SetHighColor(DarkGreen);
		SetLowColor(DarkGreen);
		break;
		}
	FillRect(box);
	}
	else
	{
	//Draw box
	//No, we are gray
	SetHighColor(DarkerGray);
	SetLowColor(DarkerGray);
	FillRect(box);
	}
	
	//Is the day the selected one?
	if (day_number == fDayNumber)
	{
	//Draw left line
	SetHighColor(Black);
	MovePenTo(box.left, box.top);
	StrokeLine(BPoint(box.left, box.bottom));
	//Draw top line
	SetHighColor(Black);
	MovePenTo(box.left, box.top);
	StrokeLine(BPoint(box.right - 1, box.top));
	//Draw bottom line
	SetHighColor(LightGray);
	MovePenTo(box.left + 1, box.bottom);
	StrokeLine(BPoint(box.right, box.bottom));
	//Draw right line
	SetHighColor(LightGray);
	MovePenTo(box.right, box.top + 1);
	StrokeLine(BPoint(box.right, box.bottom));
	
	//Remember what box it is
	fDaySelectedBox.Set(box.left, box.top, box.right, box.bottom);
	}
	else
	{
	//Draw left line
	SetHighColor(LightGray);
	MovePenTo(box.left, box.top);
	StrokeLine(BPoint(box.left, box.bottom));
	//Draw top line
	SetHighColor(LightGray);
	MovePenTo(box.left, box.top);
	StrokeLine(BPoint(box.right - 1, box.top));
	//Draw bottom line
	SetHighColor(Black);
	MovePenTo(box.left + 1, box.bottom);
	StrokeLine(BPoint(box.right, box.bottom));
	//Draw right line
	SetHighColor(Black);
	MovePenTo(box.right, box.top + 1);
	StrokeLine(BPoint(box.right, box.bottom));
	}

//If it is today, make a red thing around it
//tmp here is used over here, and is the day in the month
_IsTheDaysToday(box, DarkRed, tmp);	

DrawDate(box, day_number, box_number);
DrawDayName(box, day_number, box_number);
}

//-------------------------------------------------------------------------------
void MCalender::DrawDate(BRect box, int day_number, int box_number)
{
//Draw date
SetHighColor(Black);
SetFontSize(14);
MovePenTo(box.left + 7, box.top + 15);
fDayNumberString.SetTo("");
fDayNumberString << day_number;
DrawString(fDayNumberString.String());
}

//-------------------------------------------------------------------------------
void MCalender::DrawDayName(BRect box, int day_number, int box_number)
{
SetLowColor(Gray);
SetHighColor(Black);
SetFontSize(fBoxWidth / 6);
	//If american (the americans for some awkward reason has sunday as their first day, go figure!)
	if (fCalenderIsAmericaStyle)
	{
		for (tmp3 = 0; tmp3 <= 7; tmp3++)
		{
		MovePenTo(2 + (fBoxWidth * tmp3) - fBoxWidth, 17);
			switch (tmp3)
			{
			case 2:
			DrawString(Day1[fLanguageNumber]);
			break;
			case 3:
			DrawString(Day2[fLanguageNumber]);
			break;
			case 4:
			DrawString(Day3[fLanguageNumber]);
			break;
			case 5:
			DrawString(Day4[fLanguageNumber]);
			break;
			case 6:
			DrawString(Day5[fLanguageNumber]);
			break;
			case 7:
			DrawString(Day6[fLanguageNumber]);
			break;
			case 1:
			DrawString(Day7[fLanguageNumber]);
			break;
			}
		}
	}
	else
	{
		// i am smart && non-america :-D
		for (tmp3 = 0; tmp3 <= 7; tmp3++)
		{
		MovePenTo(2 + (fBoxWidth * tmp3) - fBoxWidth, 17);
			switch (tmp3)
			{
			case 1:
			DrawString(Day1[fLanguageNumber]);
			break;
			case 2:
			DrawString(Day2[fLanguageNumber]);
			break;
			case 3:
			DrawString(Day3[fLanguageNumber]);
			break;
			case 4:
			DrawString(Day4[fLanguageNumber]);
			break;
			case 5:
			DrawString(Day5[fLanguageNumber]);
			break;
			case 6:
			DrawString(Day6[fLanguageNumber]);
			break;
			case 7:
			DrawString(Day7[fLanguageNumber]);
			break;
			}
		}
	}
}

//-------------------------------------------------------------------------------
void MCalender::SetYear(int32 year)
{
fYear = year;
fRedrawBackground = true;
Draw(fFrame);
}

//-------------------------------------------------------------------------------
int32 MCalender::Year()
{
return fYear;
}

//-------------------------------------------------------------------------------
void MCalender::SetMonth(int32 month_number)
{
fMonthNumber = month_number;
fRedrawBackground = true;
Draw(fFrame);
}

//-------------------------------------------------------------------------------
int32 MCalender::Month()
{
return fMonthNumber;
}

//-------------------------------------------------------------------------------
void MCalender::SetDay(int32 day)
{
fDayNumber = day;
Draw(fFrame);
}

//-------------------------------------------------------------------------------
int32 MCalender::Day()
{
return fDayNumber;
}

//-------------------------------------------------------------------------------
void MCalender::SetWhen(int32 year, int32 month_number, int32 day)
{
fYear = year;
fMonthNumber = month_number;
fDayNumber = day;
fRedrawBackground = true;
Draw(fFrame);
}
//-------------------------------------------------------------------------------
void MCalender::SetBoxWidthAndHeight(int height, int width)
{
fBoxWidth = width;
fBoxHeight = height;
fRedrawBackground = true;
Draw(fFrame);
}

//-------------------------------------------------------------------------------
int MCalender::BoxHeight()
{
return fBoxHeight;
}

//-------------------------------------------------------------------------------
int MCalender::BoxWidth()
{
return fBoxWidth;
}


//-------------------------------------------------------------------------------
void MCalender::SetAmericanStyleCalender(bool style)
{
fCalenderIsAmericaStyle = style;
SetHighColor(fBackgroundColor);
FillRect(fFrame);
Draw(fFrame);
}

//-------------------------------------------------------------------------------
bool MCalender::AmericanStyleCalender()
{
return fCalenderIsAmericaStyle;
}

//-------------------------------------------------------------------------------
void MCalender::SetColorfulCalender(bool colorful)
{
fCalenderStyleIsColorful = colorful;
}

//-------------------------------------------------------------------------------
bool MCalender::ColorfulCalender()
{
return fCalenderStyleIsColorful;
}

//-------------------------------------------------------------------------------
void MCalender::SetBackgroundColor(rgb_color color)
{
fBackgroundColor = color;
SetViewColor(fBackgroundColor);
fRedrawBackground = true;
Draw(fFrame);
}

//-------------------------------------------------------------------------------
rgb_color MCalender::BackgroundColor()
{
return fBackgroundColor;
}

//-------------------------------------------------------------------------------
int32 MCalender::ThisYear()
{
int tmp_, tmp_2, tmp_3;
time(&Time);
TodayTime = localtime(&Time);

//Set what daynumber the date is
tmp_ = 0;
	for (tmp_2 = 1; tmp_ < TodayTime->tm_yday; tmp_2++)
	{
		if (tmp_ < TodayTime->tm_yday)
		{
		tmp_ += DaysInTheMonth[tmp_2];
		tmp_3 = DaysInTheMonth[tmp_2];
		}
	}
	if (tmp_3 - (tmp_ - (TodayTime->tm_yday)) + 1 == 1 && tmp_2 == 1)
	{
	return (TodayTime->tm_year + 1900 + 1);
	}
	else
	{
	return (TodayTime->tm_year + 1900);
	}
}

//-------------------------------------------------------------------------------
int32 MCalender::ThisMonth()
{
int tmp_, tmp_2, tmp_3;
time(&Time);
TodayTime = localtime(&Time);

//Set what daynumber the date is
tmp_ = 0;
	for (tmp_2 = 1; tmp_ < TodayTime->tm_yday; tmp_2++)
	{
		if (tmp_ < TodayTime->tm_yday)
		{
		tmp_ += DaysInTheMonth[tmp_2];
		tmp_3 = DaysInTheMonth[tmp_2];
		}
	}
	if (TodayTime->tm_yday == 0)
	{
	return 1;
	}
	if (tmp_3 - (tmp_ - (TodayTime->tm_yday)) + 1 > DaysInTheMonth[tmp_2 - 1])
	{
	return (tmp_2);
	}
	else
	{
		if (tmp_3 - (tmp_ - (TodayTime->tm_yday)) + 1 == 1 && tmp_2 == 1)
		{
		return 1;
		}
		else
		{
		return (tmp_2 - 1);
		}
	}
}

//-------------------------------------------------------------------------------
int32 MCalender::ThisDay()
{
int tmp_, tmp_2, tmp_3;
time(&Time);
TodayTime = localtime(&Time);

//Set what daynumber the date is
tmp_ = 0;
	for (tmp_2 = 1; tmp_ < TodayTime->tm_yday; tmp_2++)
	{
		if (tmp_ < TodayTime->tm_yday)
		{
		tmp_ += DaysInTheMonth[tmp_2];
		tmp_3 = DaysInTheMonth[tmp_2];
		}
	}
	if (TodayTime->tm_yday == 0)
	{
	return 1;
	}
	if (tmp_3 - (tmp_ - (TodayTime->tm_yday)) + 1 > DaysInTheMonth[tmp_2 - 1])
	{
	return 1;
	}
	else
	{
		if (tmp_3 - (tmp_ - (TodayTime->tm_yday)) + 1 == 1 && tmp_2 == 1)
		{
		return 1;
		}
		else
		{
		return (tmp_3 - (tmp_ - (TodayTime->tm_yday)) + 1);
		}
	}
}

//-------------------------------------------------------------------------------
void MCalender::_SetBoxBounds()
{
	//Set up the Rects
	for (tmp = 1; tmp <= 7; tmp++)
	{
		for (tmp2 = 1; tmp2 <= 6; tmp2++)
		{
		fBox[tmp][tmp2].Set((fBoxWidth * tmp) - fBoxWidth, (fBoxHeight * tmp2) - fBoxHeight + 20, 
							fBoxWidth * tmp - 1, 			 (fBoxHeight * tmp2) - 1 + 20);
		}
	}
}

//-------------------------------------------------------------------------------
void MCalender::_IsTheDaysToday(BRect frame, rgb_color color, int day)
{
int tmp_, tmp_2, tmp_3;
time(&Time);
TodayTime = localtime(&Time);

//Set what daynumber the date is
tmp_ = 0;
	for (tmp_2 = 1; tmp_ < TodayTime->tm_yday; tmp_2++)
	{
		if (tmp_ < TodayTime->tm_yday)
		{
		tmp_ += DaysInTheMonth[tmp_2];
		tmp_3 = DaysInTheMonth[tmp_2];
		}		
	}
tmp_ -= tmp_3 + 1;
tmp_ += day;

	if (day == 1 && fMonthNumber == tmp_2 && ThisMonth() == Month())
	{
	SetHighColor(color);
	StrokeRect(BRect(frame.left + 1, frame.top + 1, frame.right - 1, frame.bottom - 1));
	}

//tmp_3 = fYear;
//tmp_2 = (tmp_3 / 4);
if ( (TodayTime->tm_year)+1900 == fYear &&
	TodayTime->tm_yday == tmp_ && tmp_2 - 1 == Month())
	{
	SetHighColor(color);
	StrokeRect(BRect(frame.left + 1, frame.top + 1, frame.right - 1, frame.bottom - 1));
	}
}





