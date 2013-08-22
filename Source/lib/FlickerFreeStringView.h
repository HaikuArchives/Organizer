#ifndef	FLICKER_FREE_STRING_VIEW_H
#define FLICKER_FREE_STRING_VIEW_H
/*
** FlickerFreeStringView.h - OpenTracker's (slightly adapted) StringView replacement
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


#include <Bitmap.h>
#include <Font.h>
#include <GraphicsDefs.h>
#include <Point.h>
#include <String.h>
#include <StringView.h>

class BMessage;
class BVolume;
class BBitmap;
class BTextView;
class BView;


class OffscreenBitmap
{
	// a utility class for setting up offscreen bitmaps
	public:
		OffscreenBitmap(BRect bounds);
		OffscreenBitmap();
		~OffscreenBitmap();
	
		BView *BeginUsing(BRect bounds);
		void DoneUsing();
		BBitmap *Bitmap() const;
			// blit this to your view when you are done rendering
		BView *View() const;
			// use this to render your image
	
	private:
		void NewBitmap(BRect frame);
		BBitmap *fBitmap;
};

class FlickerFreeStringView : public BStringView
{
	// Adds support for offscreen bitmap drawing for string views that update often
	// this would be better implemented as an option of BStringView	
	public:
		FlickerFreeStringView(BRect bounds, const char *name, 
			const char *text, uint32 resizeFlags = B_FOLLOW_LEFT | B_FOLLOW_TOP,
			uint32 flags = B_WILL_DRAW);
		FlickerFreeStringView(BRect bounds, const char *name, 
			const char *text, BBitmap *existingOffscreen,
			uint32 resizeFlags = B_FOLLOW_LEFT | B_FOLLOW_TOP,
			uint32 flags = B_WILL_DRAW);
		virtual ~FlickerFreeStringView();
		virtual void Draw(BRect);
		virtual void AttachedToWindow();
		virtual void SetViewColor(rgb_color);
		virtual void SetLowColor(rgb_color);
		
	private:
		OffscreenBitmap *fBitmap;
		rgb_color fViewColor;
		rgb_color fLowColor;
		BBitmap *fOrigBitmap;
	
		typedef BStringView _inherited;
};


//class Benaphore
//{
//	// aka benaphore
//public:
//	Benaphore(const char *name = "Light Lock")
//		:	fSemaphore(create_sem(0, name)),
//			fCount(1)
//		{ }
//	
//	~Benaphore()
//		{ delete_sem(fSemaphore); }
//	
//	bool Lock()
//		{
//			if (atomic_add(&fCount, -1) <= 0)
//				return acquire_sem(fSemaphore) == B_OK;
//
//			return true;
//		}
//		
//	void Unlock()
//		{
//			if (atomic_add(&fCount, 1) < 0)
//				release_sem(fSemaphore);
//		}
//
//	bool IsLocked() const
//		{ return fCount <= 0; }
//
//private:
//	sem_id fSemaphore;
//	int32 fCount;
//};

#if B_BEOS_VERSION <= B_BEOS_VERSION_MAUI
	bool operator==(const rgb_color &, const rgb_color &);
	bool operator!=(const rgb_color &, const rgb_color &);
#endif

inline rgb_color Color(int32 r, int32 g, int32 b, int32 alpha = 255)
{
	rgb_color result;
	result.red = (uchar)r;
	result.green = (uchar)g;
	result.blue = (uchar)b;
	result.alpha = (uchar)alpha;

	return result;
}

#endif	/* FLICKER_FREE_STRING_VIEW_H */
