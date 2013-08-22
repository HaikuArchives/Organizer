/*
** FlickerFreeStringView.cpp - OpenTracker's (slightly adapted) StringView replacement
*/

/*
Open Tracker License

Terms and Conditions

Copyright (c) 1991-2000, Be Incorporated. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice applies to all licensees
and shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF TITLE, MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
BE INCORPORATED BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF, OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of Be Incorporated shall not be
used in advertising or otherwise to promote the sale, use or other dealings in
this Software without prior written authorization from Be Incorporated.

Tracker(TM), Be(R), BeOS(R), and BeIA(TM) are trademarks or registered trademarks
of Be Incorporated in the United States and other countries. Other brand product
names are registered trademarks or trademarks of their respective holders.
All rights reserved.
*/

#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <Bitmap.h>
#include <OS.h>
#include <Region.h>
#include <TextView.h>
#include <Window.h>


#include "FlickerFreeStringView.h"



const rgb_color	kBlack = {0, 0, 0, 255};
const rgb_color	kWhite = {255, 255, 255, 255};


OffscreenBitmap::OffscreenBitmap(BRect frame)
	: fBitmap(NULL)
{
	NewBitmap(frame);
}


OffscreenBitmap::OffscreenBitmap()
	: fBitmap(NULL)
{
}


OffscreenBitmap::~OffscreenBitmap()
{
	delete fBitmap;
}


void OffscreenBitmap::NewBitmap(BRect bounds)
{
	delete fBitmap;
	fBitmap = new BBitmap(bounds, B_COLOR_8_BIT, true);
	if (fBitmap->Lock())
	{
		BView *view = new BView(fBitmap->Bounds(), "", B_FOLLOW_NONE, 0);
		fBitmap->AddChild(view);

		BRect clipRect = view->Bounds();
		BRegion newClip;
		newClip.Set(clipRect);
		view->ConstrainClippingRegion(&newClip);

		fBitmap->Unlock();
	}
	else
	{
		delete fBitmap;
		fBitmap = NULL;
	}
}


BView *OffscreenBitmap::BeginUsing(BRect frame)
{
	if (!fBitmap || fBitmap->Bounds() != frame)
		NewBitmap(frame);

	fBitmap->Lock();
	return View();
}


void OffscreenBitmap::DoneUsing()
{
	fBitmap->Unlock();
}


BBitmap *OffscreenBitmap::Bitmap() const
{
	return fBitmap;
}


BView *OffscreenBitmap::View() const
{
	return fBitmap->ChildAt(0);
}


// #pragma mark -


FlickerFreeStringView::FlickerFreeStringView(BRect bounds, const char *name,
	const char *text, uint32 resizeFlags, uint32 flags)
	: BStringView(bounds, name, text, resizeFlags, flags),
	fBitmap(NULL),
	fOrigBitmap(NULL)
{
}


FlickerFreeStringView::FlickerFreeStringView(BRect bounds, const char *name,
	const char *text, BBitmap *inBitmap, uint32 resizeFlags, uint32 flags)
	: BStringView(bounds, name, text, resizeFlags, flags),
	fBitmap(NULL),
	fOrigBitmap(inBitmap)
{
}


FlickerFreeStringView::~FlickerFreeStringView()
{
	delete fBitmap;
}


void FlickerFreeStringView::Draw(BRect)
{
	BRect bounds(Bounds());
	if (!fBitmap)
		fBitmap = new OffscreenBitmap(Bounds());
	
	BView *offscreen = fBitmap->BeginUsing(bounds);

	if (Parent())
	{
		fViewColor = Parent()->ViewColor();
		fLowColor = Parent()->ViewColor();
	}

	offscreen->SetViewColor(fViewColor);
	offscreen->SetHighColor(HighColor());
	offscreen->SetLowColor(fLowColor);

	BFont font;
    GetFont(&font);
	offscreen->SetFont(&font);

	offscreen->Sync();
	if (fOrigBitmap)
		offscreen->DrawBitmap(fOrigBitmap, Frame(), bounds);
	else
		offscreen->FillRect(bounds, B_SOLID_LOW);

	if (Text())
	{
		BPoint loc;

		font_height	height;
		GetFontHeight(&height);

		edge_info eInfo;
		switch (Alignment()) {
			case B_ALIGN_LEFT:
				{
					// If the first char has a negative left edge give it
					// some more room by shifting that much more to the right.
					font.GetEdges(Text(), 1, &eInfo);
					loc.x = bounds.left + (2 - eInfo.left);
					break;
				}
				
			case B_ALIGN_CENTER:
				{
					float width = StringWidth(Text());
					float center = (bounds.right - bounds.left) / 2;
					loc.x = center - (width/2);
					break;
				}
				
			case B_ALIGN_RIGHT:
				{
					float width = StringWidth(Text());
					loc.x = bounds.right - width - 2;
					break;
				}
		}
		loc.y = bounds.bottom - (1 + height.descent);
		offscreen->MovePenTo(loc);
		offscreen->DrawString(Text());
	}
	offscreen->Sync();
	SetDrawingMode(B_OP_COPY);
	DrawBitmap(fBitmap->Bitmap());
	fBitmap->DoneUsing();
}


void FlickerFreeStringView::AttachedToWindow()
{
	_inherited::AttachedToWindow();
	if (Parent())
	{
		fViewColor = Parent()->ViewColor();
		fLowColor = Parent()->ViewColor();
	}
	SetViewColor(B_TRANSPARENT_32_BIT);
	SetLowColor(B_TRANSPARENT_32_BIT);
}


void FlickerFreeStringView::SetViewColor(rgb_color color)
{
	if (fViewColor != color)
	{
		fViewColor = color;
		Invalidate();
	}
	_inherited::SetViewColor(B_TRANSPARENT_32_BIT);
}


void FlickerFreeStringView::SetLowColor(rgb_color color)
{
	if (fLowColor != color)
	{
		fLowColor = color;
		Invalidate();
	}
	_inherited::SetLowColor(B_TRANSPARENT_32_BIT);
}


// #pragma mark -

#if B_BEOS_VERSION <= B_BEOS_VERSION_MAUI

bool operator==(const rgb_color &a, const rgb_color &b)
{
	return a.red == b.red
		&& a.green == b.green
		&& a.blue == b.blue
		&& a.alpha == b.alpha;
}


bool operator!=(const rgb_color &a, const rgb_color &b)
{
	return !operator==(a, b);
}

#endif
