//-----------------------  Local includes  ----------------------
#include "CustomListItem.h"

//----------------------- Global includes  ----------------------
const rgb_color BeBackgroundGrey = 		{216,216,216,	255};
const rgb_color BeInactiveControlGrey = {240,240,240,	255};
const rgb_color BeFocusBlue =			{0,  0,  229,	255};
const rgb_color BeHighlight =			{255,255,255,	255};
const rgb_color BeShadow =				{152,152,152,	255};
const rgb_color BeDarkShadow =			{108,108,108,	255};
const rgb_color BeLightShadow =			{194,194,194,	255};
const rgb_color BeButtonGrey =			{232,232,232,	255};
const rgb_color BeInactiveGrey =		{127,127,127,	255};
const rgb_color BeListSelectGrey =		{178,178,178,	255};
const rgb_color BeTitleBarYellow =		{255,203,0,		255};
const rgb_color BeBack =				(ui_color(B_PANEL_BACKGROUND_COLOR));
const rgb_color Red =					{250, 10, 10,	255};
const rgb_color DimRed =				{230, 100, 100,	255};
const rgb_color Black =					{0, 0, 0,	255};

//---------------------------------------------------------------
MCustomListItem::MCustomListItem(const char* title, const char* list_type)
			 : BListItem()
{
fTitle.SetTo(title);
fType.SetTo(list_type);
}

//---------------------------------------------------------------
MCustomListItem::~MCustomListItem()
{

}

//---------------------------------------------------------------
void MCustomListItem::DrawItem(BView *owner, BRect frame, bool complete)
{
	if (IsSelected() || complete)
	{
	rgb_color color;
		if (IsSelected())
		{
		color = BeLightShadow;
		}
		else
		{
		color = owner->ViewColor();
		}
		owner->SetLowColor(color);
		owner->SetHighColor(color);
		owner->FillRect(frame); 
	}
	if (IsEnabled())
	{
	owner->SetHighColor(Red);
	}
	else
	{
	owner->SetHighColor(DimRed);
	}
	owner->MovePenTo(frame.left + 5, frame.bottom - 2);
	owner->DrawString(fType.String());
	owner->MovePenTo(frame.left + 60, frame.bottom - 2);
	if (IsEnabled())
	{
	owner->SetHighColor(Black);
	}
	else
	{
	owner->SetHighColor(BeDarkShadow);
	}
	owner->DrawString(fTitle.String());
}

//---------------------------------------------------------------
const char* MCustomListItem::Type()
{
	return fType.String();
}

//---------------------------------------------------------------
const char* MCustomListItem::Title()
{
	return fTitle.String();
}
