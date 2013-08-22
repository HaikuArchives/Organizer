#include "Bubble.h"

//-----------------------------------------------------------------
MBubble::MBubble(const char* name, const char* text) : BMessage('Bubl')
{
while(!be_app_messenger.IsValid())
        snooze(200000);
left = 10;
top = 10;
right = 100;
bottom = 26;
width = right - left;
height = bottom - top;
Black.red = Black.green = Black.blue = 0;
White.red = White.green = White.blue = 255;
High_Color.red = 100;
High_Color.green = 0;
High_Color.blue = 0;
Low_Color.red = 100;
Low_Color.green = 100;
Low_Color.blue = 100;
View_Color.red = 241;
View_Color.green = 209;
View_Color.blue = 89;
View_Color.alpha = 170;

be_plain_font->GetHeight(&fontheight);

Window_Rect.Set(left, top, right, bottom);

BubbleWindow = new BWindow(Window_Rect, "BubbleWindow", B_NO_BORDER_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL, 
							B_NOT_RESIZABLE | B_NOT_MOVABLE | B_AVOID_FOCUS, B_ALL_WORKSPACES);

BubbleView = new BView(BubbleWindow->Bounds(), NULL, B_FOLLOW_ALL, 0);
BubbleView->SetHighColor(High_Color);
BubbleView->SetLowColor(Low_Color);
BubbleView->SetDrawingMode(B_OP_ALPHA);
BubbleBGView = new BView(BubbleWindow->Bounds(), NULL, B_FOLLOW_ALL, 0);
BubbleBGView->SetHighColor(High_Color);
BubbleBGView->SetLowColor(Low_Color);
BubbleBGView->SetDrawingMode(B_OP_ALPHA);
//make it black so that the edge becomes black
BubbleView->SetViewColor(Black);

// -  and  + 1 to make it have a Black edge
BubbleTextView = new BTextView(BRect(BubbleWindow->Bounds().left + 1, BubbleWindow->Bounds().top + 1,
									 BubbleWindow->Bounds().right - 1, BubbleWindow->Bounds().bottom - 1),
							 "", BRect(2, 0, 1600, (bottom - top)), B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
BubbleTextView->MakeEditable(false);
BubbleTextView->MakeSelectable(false);
BubbleTextView->SetWordWrap(false);
BubbleTextView->SetHighColor(High_Color);
BubbleTextView->SetLowColor(Low_Color);
BubbleTextView->SetViewColor(View_Color);
BubbleTextView->SetText(text);
BubbleTextView->SetFontSize(12);
BubbleTextView->SetDrawingMode(B_OP_ALPHA);

//BubbleView->AddChild(BubbleTextView);
//BubbleWindow->AddChild(BubbleView);
BubbleWindow->AddChild(BubbleBGView);
BubbleWindow->Run();
}

//-----------------------------------------------------------------
MBubble::~MBubble()
{

}

//-----------------------------------------------------------------
void MBubble::Hide()
{
BubbleWindow->Lock();
if (!BubbleWindow->IsHidden())
	{
	BubbleWindow->Hide();
	}
BubbleWindow->Unlock();
}

//-----------------------------------------------------------------
void MBubble::SetText(const char* text)
{
BubbleWindow->Lock();
BubbleTextView->SetText(text);
Bubble_Text.SetTo(text);
BubbleWindow->Unlock();
}


//-----------------------------------------------------------------
void MBubble::Show()
{
BubbleWindow->Lock();
Bubble_Text.SetTo(BubbleTextView->Text());
if (Bubble_Text.Length() !=  0)
{
	if (BubbleWindow->IsHidden())
	{
	/************************************************************/
	/********** Thanks to Werner Freytag for this code **********/
	/************************************************************/
	uint32 location;
	Mouse_Location.Set(0, 0);
	BScreen Screen(BubbleWindow);
	width = (int)BubbleTextView->LineWidth(0);
	width = width + 10;
	BubbleWindow->ResizeTo(width, height);
	BubbleBGView->ResizeTo(width, height);
	BubbleBGView->GetMouse(&Mouse_Location, &location, false);
	BubbleWindow->MoveBy((Mouse_Location.x + 2), (Mouse_Location.y - 12));
	BRect	Rect = BRect(BubbleWindow->Frame());
	BBitmap *bgbitmap = new BBitmap(Rect.OffsetToCopy(0,0), Screen.ColorSpace(), true );
	Screen.ReadBitmap(bgbitmap, false, &Rect);

	//-------
	bgbitmap->Lock();
	bgbitmap->AddChild(BubbleView);
	BubbleView->ResizeTo(width, height);
	BRect frame = BRect(0, 0, Rect.Width()-2, Rect.Height()-2);
	BubbleView->SetDrawingMode(B_OP_ALPHA);
	
	BubbleView->SetHighColor(0, 0, 0, 20);
	frame.OffsetBy(1,1);
	BubbleView->FillRoundRect(frame, 5, 5 );

	frame.OffsetBy(-1,-1);

	BubbleView->SetHighColor(255, 255, 255, 180);
	BubbleView->FillRoundRect(frame, 4, 3);

	BubbleView->SetHighColor(255, 255, 255, 220);
	BubbleView->StrokeRoundRect(frame.InsetByCopy(0.5, 0.5).OffsetToCopy(1.0, 1.0), 4, 3);

	BubbleView->SetHighColor(0, 0, 0, 150);
	BubbleView->StrokeRoundRect(frame, 4, 3);
	
	BubbleView->SetHighColor(0, 0, 0);

	float line_height = fontheight.ascent + fontheight.descent + fontheight.leading;
	float numlines = 1;

	BString Text = BubbleTextView->Text();
	Text.ReplaceAll("\t", "   ");
	
	int start = 0, ende;
		for (int i = 0; i < numlines; i++) 
		{
			ende = Text.FindFirst("\n", start); if (ende<0) ende = Text.Length();
			char* text = new char[ende - start + 1];
			Text.CopyInto(text, start, ende - start);
			text[ende - start] = 0;
		
			BubbleView->DrawString( text, BPoint(5, 2 + fontheight.ascent + i * line_height) );
			start = ende + 1;
		}

	bgbitmap->RemoveChild(BubbleView);
	bgbitmap->Unlock();

	BubbleBGView->SetViewBitmap(bgbitmap);
	BubbleView->Invalidate();
	delete bgbitmap;
	//BubbleWindow->ResizeTo((BubbleTextView->TextLength()) * 8 /*max char width*/, height);
	BubbleWindow->Show();
	//uint32 location;
	//Mouse_Location.Set(0, 0);
	//BubbleView->GetMouse(&Mouse_Location, &location, false);
	//BubbleWindow->MoveBy((Mouse_Location.x + 2), (Mouse_Location.y - 12));
	}
}	
BubbleWindow->Unlock();
}

//-----------------------------------------------------------------
const char* MBubble::Text()
{
Bubble_Text.SetTo(BubbleTextView->Text());
return(Bubble_Text.String());
}
