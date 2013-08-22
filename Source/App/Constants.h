//----------------------------------------------------------------------
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <AppKit.h>
#include <SupportKit.h>
#include <InterfaceKit.h>
#include <StorageKit.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <OS.h>
#include <Deskbar.h>
#include <GraphicsDefs.h>
#include "../lib/Kit.h"

//----------------------------------------------------------------------

#define MSG_ABOUT				'1001' //Open the about window
#define MSG_OPEN				'1002' //Open
#define MSG_SAVE				'1003' //Save
#define MSG_VIEW				'1004' //
#define MSG_QUIT				'1005' //Quit
#define MSG_CALENDER			'1006' //Calender is clicked
#define MSG_PREFERENCES			'1007' //Open the preferences window
#define MSG_ADD_APOINTMENT		'1008' //Delete all items that day
#define MSG_ADD_SCRIPT			'1009' //Add a note with running of a script
#define MSG_ADD_NOTE			'1010' //Add note on this day
#define MSG_DELETE_SCRIPT		'1011' //Delete script
#define MSG_DELETE_APOINTMENT	'1012' //Delete apointment
#define MSG_DELETE_NOTE			'1013' //Delete note
#define MSG_APPLY_THEME			'1014' //Apply theme
#define MSG_CHANGE_YEAR			'1015' //Change the calenderyear
#define MSG_CHANGE_MONTH		'1016' //Change the calendermonth
#define MSG_ADD_SOMETHING		'1017' //Add something
#define	MSG_REMOVE_SOMETHING	'1018' //Remove what is selected in the noteview
#define MSG_NEW_ITEM_SELECTED	'1019' //Something in the list has been selected
#define MSG_EDIT_SOMETHING		'1020' //edit something
#define MSG_SAVE_SCRIPT			'1021' //Save the new/overwrite old script
#define MSG_SAVE_NOTE			'1022' //Save the new/overwrite old note
#define MSG_SAVE_APOINTMENT		'1023' //Save the new/overwrite old apointment
#define MSG_BOGUS				'1337' //Message that isnt needed to be intercepted
#define MSG_EDIT_SCRIPT_WIN		'1024' //Open the edit window
#define MSG_ADD_SCRIPT_WIN		'1025' //Open the edit window in Add mode	
#define MSG_EDIT_NOTE_WIN		'1026' //Open the note window
#define MSG_ADD_NOTE_WIN		'1027' //Open the note window in Add mode	
#define MSG_EDIT_APOINTMENT_WIN	'1028' //Open the Apointment window
#define MSG_ADD_APOINTMENT_WIN	'1029' //Open the Apointment window in Add mode	
//#define MSG_INVALIDATE_LISTVIEW	'1030' //Redraw the listview
#define MSG_GET_NOTES			'1030' //Get notes and add them to the list
#define MSG_RUN_SCRIPT_CHECKBOX	'1031' //Run the script or not?
#define MSG_CANCEL				'1032' //cancel
#define MSG_NOTIFY_APOINTMENT_CHECKBOX	'1034' //Notify me?
#define MSG_CALENDER_STYLE		'1034' //CalenderStyle
#define MSG_CALENDER_COLORFUL	'1035' //Colorful calender?
#define MSG_LANGUAGE_CHANGED	'1036' //New language selected
#define MSG_OPEN_GL_GAME		'1037' //Open the Secret OpenGL Game
#define MSG_CLOSE_GL_GAME		'1038' //Close the Secret OpenGL Game
#define MSG_QUIT_PLEASE			'1039' //Kill threads please
#define MSG_HISTORY_SCRIPT_ITEM_SELECTED '1040' //HistoriItem selected
#define MSG_AUTOUPDATE			'1040' //Preferences for autoupdate
#define MSG_EXPORT_HTML			'1041' //Open the export html window
#define MSG_EXPORT				'1042' //Start exporting
#define MSG_EXPORT_HTML_FILE	'1043' //Select where to export it to:
#define MSG_EXPORT_FILENAME_CHANGED '1044' //TextControlfilename has changed

//----------------------------------------------------------------------

extern const char* 				STR_APP_NAME;
extern const char* 				STR_EXEC_FILE_NAME;
extern const char*				GET_NEW_VERSION_PATH;
extern const char* 				GET_NEW_URL_PATH;
extern const char* 				STR_VERSIONNUMBER;
extern const char* 				STR_AUTHOR;
extern const char* 				STR_AUTHOR_EMAIL;
extern const char* 				STR_AUTHOR_NICK;
extern const char* 				STR_WEBPAGE;

extern const char*				SAVE_WINDOW_RECT;
extern const char*				SAVE_FILE_NAME;
extern const char*				SAVE_PATH_PART_1;
extern const char*				SAVE_PATH_PART_2;
extern const char*				SAVE_PATH_PART_3_1;
extern const char*				SAVE_PATH_PART_3_2;
extern const char*				SAVE_PATH_PART_3_3;
extern const char*				SAVE_SETTINGS_PATH;
extern const char*				SAVE_NOTE_PATH;
extern const char*				SAVE_HISTORY_PATH;
extern const char*				SAVE_SCRIPT_PATH;
extern const char* 				SAVE_UPDATE_VERSION;
extern const char* 				SAVE_UPDATE_URL;

extern const char*				SAVE_FILE_TITLE;
extern const char*				SAVE_FILE_NOTE;
extern const char*				SAVE_FILE_NOTIFY;
extern const char*				SAVE_FILE_TIME;
extern const char*				SAVE_FILE_TYPE;
extern const char*				SAVE_FILE_PATH;

extern const char* 				NAME_EXEC_DIR; //Path to executable directory
extern const char* 				NAME_CHECK_FOR_UPDATES; //Bool, check for updates or not
extern const char* 				NAME_CALENDER_STYLE;
extern const char* 				NAME_LANGUAGE;
extern const char* 				NAME_THEME;
extern const char* 				NAME_CALENDER_COLORFUL;

extern const char* 				STR_LANGUAGES[5];
extern const char* 				STR_YEAR[5];
extern const char* 				STR_MONTH[5];
extern const char* 				STR_MONTHNAMES[13][5];
extern const char* 				STR_DELETE[5];
extern const char*				STR_ADD_NOTE[5];
extern const char* 				STR_ADD_APOINTMENT[5];
extern const char* 				STR_ADD_SCRIPT[5];
extern const char* 				STR_OPEN[5];
extern const char* 				STR_FILE[5];
extern const char* 				STR_EDIT[5];
extern const char* 				STR_VIEW[5];
extern const char* 				STR_ABOUT[5];
extern const char* 				STR_QUIT[5];
extern const char* 				STR_PREFERENCES[5];
extern const char* 				STR_SETTINGS[5];
extern const char* 				STR_SAVE[5];
extern const char* 				STR_DONT_SAVE[5];
extern const char* 				STR_OK[5];
extern const char* 				STR_CALENDER[5];
extern const char* 				STR_EDIT[5];
extern const char* 				STR_ADD[5];
extern const char* 				STR_REMOVE[5];
extern const char* 				STR_SAVE[5];
extern const char* 				STR_SCRIPT_NAME[5];
extern const char* 				STR_APOINTMENT_NAME[5];
extern const char* 				STR_RUN_SCRIPT_AT[5];
extern const char* 				STR_NOTIFY_ME_AT[5];
extern const char* 				STR_OLD_SCRIPTS[5];
extern const char* 				STR_ADD_SCRIPT_WIN[5];
extern const char* 				STR_EDIT_SCRIPT_WIN[5];
extern const char* 				STR_ADD_NOTE_WIN[5];
extern const char* 				STR_EDIT_NOTE_WIN[5];
extern const char* 				STR_ADD_APOINTMENT_WIN[5];
extern const char* 				STR_EDIT_APOINTMENT_WIN[5];
extern const char* 				STR_PREFERENCES_WINDOW[5];
extern const char* 				STR_ABOUT_WINDOW[5];
extern const char* 				STR_NOTE_NAME[5];
extern const char*				STR_MISSING_TITLE[5];
extern const char* 				STR_RUN_SCRIPT[5];
extern const char* 				STR_NOTIFY_ME[5];
extern const char* 				STR_CANCEL[5];
extern const char*				STR_SAVE_CHANGES[5];
extern const char*				STR_LANGUAGE[5];
extern const char*				STR_COLORFUL_CALENDER[5];
extern const char*				STR_AMERICAN_CALENDER[5];
extern const char* 				STR_STYLE[5];
extern const char* 				STR_LANGUAGE_ALERT[5];
extern const char* 				STR_RESTART_NOW[5];
extern const char* 				STR_RESTART_LATER[5];
extern const char* 				STR_YES[5];
extern const char* 				STR_NO[5];
extern const char* 				STR_NO_NEVER[5];
extern const char* 				STR_A_NEW_VERSION_IS_AVAILABLE[5];
extern const char*				STR_HIDDEN_OPENGL_GAME[5];
extern const char*				STR_HISTORY[5];
extern const char*				STR_OTHER_SETTINGS[5];
extern const char*				STR_AUTOUPDATE[5];
extern const char*				STR_NOTE[5];
extern const char*				STR_APOINTMENT[5];
extern const char*				STR_SCRIPT[5];
extern const char*				STR_ADD_WHAT[5];
extern const char*				STR_INCLUDE_NOTE[5];
extern const char*				STR_INCLUDE_APOINTMENT[5];
extern const char* 				STR_EXPORT[5];
extern const char* 				STR_EXPORT_WINDOW[5];
extern const char* 				STR_EXPORT_HTML[5];
extern const char* 				STR_EXPORT_TO[5];
extern const char* 				STR_BY[5];
extern const char* 				STR_ALSO_KNOWN_AS[5];
extern const char* 				STR_FILENAME[5];
extern const char* 				STR_VERSION_NUMBER[5];
extern const char* 				STR_BUILD_NUMBER[5];

extern int						INT_LANGUAGE;
extern int						INT_YEAR;
extern int						INT_MONTH;
extern int						INT_DAY;
extern int						INT_THEME;
extern int						INT_CHARSIZE;
extern int						INT_MAXFILES;

extern int						BUILD_NUMBER;

extern bool 					BOOL_AMERICAN_STYLE;
extern bool						BOOL_COLORFUL_CALENDER;

//----------------------------------------------------------------------

//Be standard UI colors
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

//Other colors
const rgb_color Black =					{0,  0,  0,		255};
const rgb_color White =					{255,255,255,	255};
const rgb_color Red =					{255,0,  0,		255};
const rgb_color Green =					{0,  167,0,		255};
const rgb_color LightGreen =			{90, 240,90,	255};
const rgb_color Blue =					{49, 61, 225,	255};
const rgb_color LightBlue =				{64, 162,255,	255};
const rgb_color Purple =				{144,64, 221,	255};
const rgb_color LightPurple =			{166,74, 255,	255};
const rgb_color Lavender =				{193,122,255,	255};
const rgb_color Yellow =				{255,203,0,		255};
const rgb_color Orange =				{255,163,0,		255};
const rgb_color Flesh =					{255,231,186,	255};
const rgb_color Tan =					{208,182,121,	255};
const rgb_color Brown =					{154,110,45,	255};
const rgb_color Grey = 					{200,200,200,	255};
const rgb_color LightMetallicBlue =		{143,166,240,	255};
const rgb_color MedMetallicBlue =		{75, 96, 154,	255};
const rgb_color DarkMetallicBlue =		{78, 89, 126,	255};
const rgb_color PineAppleGreen =		{183,200,184,	255};
const rgb_color PineAppleYellow =		{254,248,224,	255};
const rgb_color PineAppleDarkGreen =	{163,180,164,	255};
const rgb_color DiscreetGray =			{128,128,128,	255};
const rgb_color DiscreetLightGray =		{191,191,191,	255};
const rgb_color DiscreetYellow =		{234,203,86,	255};
#endif
