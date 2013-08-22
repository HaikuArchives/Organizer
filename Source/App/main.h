#ifndef _mApp_h_
#define _mApp_h_

#define ApplicationSignature "application/x-vnd.fSub.Organizer"

#include "Constants.h"
#include "mWindow.h"
#include "aboutWindow.h"
#include "preferencesWindow.h"
#include "editWindow.h"
#include "exportWindow.h"
#include "Secret/glWindow.h"

class mApp : public BApplication
{
public:
							mApp();
							~mApp();
	virtual void			ReadyToRun();
	virtual void			MessageReceived(BMessage *message);
	virtual void 			RefsReceived(BMessage *message);
	void					LoadSettings();
	
private:
	mWindow				*	_mWindow;
	AboutWindow			*	_AboutWindow;
	PreferencesWindow	*	_PreferencesWindow;
	EditWindow			*	_EditWindow;
	ExportWindow		*	_ExportWindow;
	Wind				*	_Wind;
	
	BFilePanel			*	mFilePanel;
	
	BPath 					path;
	BString 				tmp;
	BString					tmp2;
	bool					CheckForUpdates;
	bool					RunNotification;
	bool					Show;
	
	thread_id				CheckForUpdate;
	static int32 			CheckForUpdateThread_static(void *data);
	void 					CheckForUpdateThread();
	
	thread_id				Notification;
	static int32 			NotificationThread_static(void *data);
	void					NotificationThread();
};

#endif
