#include "Constants.h"

extern const char* STR_APP_NAME = 			"fSub Organizer";
extern const char* STR_EXEC_FILE_NAME =		"Organizer";
extern const char* GET_NEW_VERSION_PATH = 	"http://ibar.sourceforge.net/fSub/Files/Organizer-Version.txt";
extern const char* GET_NEW_URL_PATH = 		"http://ibar.sourceforge.net/fSub/Files/Organizer-URL.txt";
extern const char* STR_VERSIONNUMBER = 	"0.1";
extern const char* STR_AUTHOR =				"Marius Stene";
extern const char* STR_AUTHOR_EMAIL =		"m_stene@yahoo.com";
extern const char* STR_AUTHOR_NICK =		"Mariux";
extern const char* STR_WEBPAGE =			"http://ibar.sourceforge.net/fSub";

extern const char* SAVE_WINDOW_RECT =		"WindowRect";
extern const char* SAVE_FILE_NAME =			"settings";
extern const char* SAVE_PATH_PART_1 =		"/fSub";
extern const char* SAVE_PATH_PART_2 =		"/Organizer";
extern const char* SAVE_PATH_PART_3_1 =		"/Settings";
extern const char* SAVE_PATH_PART_3_2 =		"/Notes";
extern const char* SAVE_PATH_PART_3_3 =		"/History";
extern const char* SAVE_SETTINGS_PATH =		"/fSub/Organizer/Settings/";
extern const char* SAVE_NOTE_PATH =			"/fSub/Organizer/Notes/";
extern const char* SAVE_HISTORY_PATH =		"/fSub/Organizer/History/";
extern const char* SAVE_SCRIPT_PATH =		"/Scripts/";
extern const char* SAVE_UPDATE_VERSION =	"/var/tmp/Organizer-Version.txt";
extern const char* SAVE_UPDATE_URL =		"/var/tmp/Organizer-URL.txt";

extern const char* SAVE_FILE_TITLE =		"Title";
extern const char* SAVE_FILE_NOTE =			"Note";
extern const char* SAVE_FILE_NOTIFY =		"Notify";
extern const char* SAVE_FILE_TIME =			"Time";
extern const char* SAVE_FILE_TYPE =			"Type";
extern const char* SAVE_FILE_PATH =			"Path";

extern const char* NAME_EXEC_DIR =			"execDir";
extern const char* NAME_CHECK_FOR_UPDATES =	"CheckForUpdates";
extern const char* NAME_CALENDER_STYLE =	"AmericanStyleCalender";
extern const char* NAME_CALENDER_COLORFUL =	"CalenderColorful";
extern const char* NAME_LANGUAGE =			"Language";
extern const char* NAME_THEME =				"Theme";

extern const char* STR_LANGUAGES[5] = 		{"English", "Norsk", "<empty>", "<empty>", "<empty>"};
extern const char* STR_YEAR[5] = 			{"Year", "År", "delete", "delete", "delete"};
extern const char* STR_MONTH[5] = 			{"Month", "Måned", "delete", "delete", "delete"};
extern const char* STR_MONTHNAMES[13][5] =	{{"error", "error", "error", "error", "error"},
											{"January", "Januar", "January", "January", "January"},
											{"February", "Februar",	"February", "February", "February"},
											{"March", "Mars", "March", "March", "March"},
											{"April", "April", "April", "April", "April"},
											{"May", "Mai", "May", "May", "May"},
											{"June", "Juni", "June", "June", "June"},
											{"July", "Juli", "July", "July", "July"},
											{"August", "August", "August", "August", "August"},
											{"September", "September", "September", "September", "September"},
											{"October", "Oktober", "October", "October", "October"},
											{"November", "November", "November", "November", "November"},
											{"December", "Desember", "December", "December", "December"}};
											
extern const char* STR_DELETE[5] =	 		{"Delete", "Slett", "delete", "delete", "delete"};
extern const char* STR_ADD_NOTE[5] = 		{"Add Note", "Legg Til Notat", "delete", "delete", "delete"};
extern const char* STR_ADD_APOINTMENT[5] = 	{"Add Apointment", "Legg Til Avtale ", "delete", "delete", "delete"};
extern const char* STR_ADD_SCRIPT[5] = 		{"Add Script", "Legg Til Skript", "delete", "delete", "delete"};
extern const char* STR_OPEN[5] = 			{"Open", "Åpne", "delete", "delete", "delete"};
extern const char* STR_FILE[5] = 			{"File", "Fil", "delete", "delete", "delete"};
extern const char* STR_EDIT[5] = 			{"Edit", "Rediger", "delete", "delete", "delete"};
extern const char* STR_VIEW[5] = 			{"View", "Vindu", "delete", "delete", "delete"};
extern const char* STR_ABOUT[5] = 			{"About", "Om", "delete", "delete", "delete"};
extern const char* STR_QUIT[5] = 			{"Quit", "Avslutt", "delete", "delete", "delete"};
extern const char* STR_PREFERENCES[5] =		{"Preferences", "Instillinger", "delete", "delete", "delete"};
extern const char* STR_SETTINGS[5] =		{"Settings", "Instillinger", "delete", "delete", "delete"};
extern const char* STR_SAVE[5] = 			{"Save", "Lagre", "delete", "delete", "delete"};
extern const char* STR_DONT_SAVE[5] = 		{"Don't Save", "Ikke Lagre", "delete", "delete", "delete"};
extern const char* STR_OK[5] = 				{"OK", "Greit", "delete", "delete", "delete"};
extern const char* STR_CALENDER[5] = 		{"Calender", "Kalender", "delete", "delete", "delete"};
extern const char* STR_ADD[5] =				{"Add", "Legg til", "Add", "Add", "Add"};
extern const char* STR_REMOVE[5] =			{"Remove", "Fjern", "Remove", "Remove", "Remove"};
extern const char* STR_SCRIPT_NAME[5] =		{"Script Name", "Navn På Skript", "Remove", "Remove", "Remove"};
extern const char* STR_APOINTMENT_NAME[5] =	{"Apointment Name", "Navn på avtale", "Remove", "Remove", "Remove"};
extern const char* STR_RUN_SCRIPT_AT[5] =	{"Run Script At", "Kjør Skriptet Klokken", "Remove", "Remove", "Remove"};
extern const char* STR_NOTIFY_ME_AT[5] =	{"Notify Me At", "Si ifra klokken", "Remove", "Remove", "Remove"};
extern const char* STR_OLD_SCRIPTS[5] =		{"Old Scripts", "Gamle Skripter", "Remove", "Remove", "Remove"};
extern const char* STR_EDIT_SCRIPT_WIN[5] =	{"Edit A Scriptfile", "Skript Vindu", "Remove", "Remove", "Remove"};
extern const char* STR_ADD_SCRIPT_WIN[5] =	{"Add A Scriptfile", "Skript Vindu", "Remove", "Remove", "Remove"};
extern const char* STR_ADD_NOTE_WIN[5] =	{"Add A Note", "Notatvindu", "Remove", "Remove", "Remove"};
extern const char* STR_EDIT_NOTE_WIN[5] =	{"Edit A Note", "Notatvindu", "Remove", "Remove", "Remove"};
extern const char* STR_ADD_APOINTMENT_WIN[5]={"Add An Apointment", "Avtalevindu", "Remove", "Remove", "Remove"};
extern const char* STR_EDIT_APOINTMENT_WIN[5]={"Edit An Apointment", "Avtalevindu", "Remove", "Remove", "Remove"};
extern const char* STR_PREFERENCES_WINDOW[5] = {"Preferences", "Instillinger", "Remove", "Remove", "Remove"};
extern const char* STR_ABOUT_WINDOW[5] =	{"About fishingSubmarine Organizer", "Om fishingSubmarine Organizer", "Remove", "Remove", "Remove"};
extern const char* STR_NOTE_NAME[5] = 		{"Note Name", "Notatnavn", "Remove", "Remove", "Remove"};
extern const char* STR_MISSING_TITLE[5] =	{"Please supply a title!", "Tittel plz", "Remove", "Remove", "Remove"};
extern const char* STR_RUN_SCRIPT[5] =		{"Run Script", "Kjør Skript", "Remove", "Remove", "Remove"};
extern const char* STR_NOTIFY_ME[5] =		{"Notify Me", "Si ifra", "Remove", "Remove", "Remove"};
extern const char* STR_CANCEL[5] =			{"Cancel", "Angre", "Remove", "Remove", "Remove"};
extern const char* STR_SAVE_CHANGES[5] =	{"Save changes?", "Lagre endringer?", "Remove", "Remove", "Remove"};
extern const char* STR_LANGUAGE[5] =		{"Language", "Språk", "Remove", "Remove", "Remove"};
extern const char* STR_COLORFUL_CALENDER[5] ={"Multicolor Calender", "Flerfarget kalender", "Remove", "Remove", "Remove"};
extern const char* STR_AMERICAN_CALENDER[5] ={"Sunday Is First", "Søndag er første dag", "Remove", "Remove", "Remove"};
extern const char* STR_STYLE[5] =			{"Style", "Stil", "Remove", "Remove", "Remove"};
extern const char* STR_LANGUAGE_ALERT[5] =	{"The application has to be restarted for the language changes to be applied", "Programmet må startes på nytt for at språkinstillingene skal fungere", "Remove", "Remove", "Remove"};
extern const char* STR_RESTART_NOW[5] =		{"Restart now", "Starte på nytt nå", "Remove", "Remove", "Remove"};
extern const char* STR_RESTART_LATER[5] =	{"Restart later", "Starte på nytt senere", "Remove", "Remove", "Remove"};
extern const char* STR_YES[5] =				{"Yes", "Ja", "Remove", "Remove", "Remove"};
extern const char* STR_NO[5] =				{"No", "Nei", "Remove", "Remove", "Remove"};
extern const char* STR_NO_NEVER[5] =		{"No, and never ask me again", "Nei, og aldri spør meg igjen!", "Remove", "Remove", "Remove"};
extern const char* STR_A_NEW_VERSION_IS_AVAILABLE[5] =
											{"A new version of fSub Organizer is available, do you want to download it?",
											"En ny versjon av fSub Organizer er filgjengelig, ønsker du å laste den ned?",
											"Remove",
											"Remove",
											"Remove"};
extern const char* STR_HIDDEN_OPENGL_GAME[5] ={"Hidden OpenGL-Game", "Hemmelig OpenGL-spill", "Remove", "Remove", "Remove"};
extern const char* STR_HISTORY[5] =			{"History", "Historie", "Remove", "Remove", "Remove"};
extern const char* STR_OTHER_SETTINGS[5] =	{"Other Settings", "Andre Instillinger", "Remove", "Remove", "Remove"};
extern const char* STR_AUTOUPDATE[5] =		{"Notify me when a new version is available", "Si ifra når en ny versjon er klar for nedlastning", "Remove", "Remove", "Remove"};
extern const char* STR_NOTE[5] = 			{"Note", "Notat", "Remove", "Remove", "Remove"};
extern const char* STR_APOINTMENT[5] = 		{"Apointment", "Avtale", "Re3move", "R4emove", "Remo5ve"};
extern const char* STR_SCRIPT[5] = 			{"Script", "Skript", "Remove", "Remove", "Remove"};
extern const char* STR_ADD_WHAT[5] = 		{"What would you like to add?", "Hva vil du legge til?", "Remove", "Remove", "Remove"};
extern const char* STR_INCLUDE_NOTE[5] =	{"Include notes", "Inkluder notater", "Remove", "Remove", "Remove"};
extern const char* STR_INCLUDE_APOINTMENT[5] ={"Include apointments", "Inkluder avtaler", "Remove", "Remove", "Remove"};
extern const char* STR_EXPORT[5] = 			{"Export", "Eksporter", "Remove", "Remove", "Remove"};
extern const char* STR_EXPORT_WINDOW[5] =	{"Export Notes And Apointments From This Month To HTML", "Eksporter notater og avtaler fra denne måneden til HTML", "Remove", "Remove", "Remove"};
extern const char* STR_EXPORT_HTML[5] = 	{"Export to HTML", "Eksporter til html", "Remove", "Remove", "Remove"};
extern const char* STR_EXPORT_TO[5] = 		{"Export to Folder", "Eksporter til mappe", "Remove", "Remove", "Remove"};
extern const char* STR_BY[5] =				{"By", "Av", "Remove", "Remove", "Remove"};
extern const char* STR_ALSO_KNOWN_AS[5] =	{"Also known as", "Også kjent som", "Remove", "Remove", "Remove"};
extern const char* STR_FILENAME[5] =		{"Filename", "Filnavn", "Remove", "Remove", "Remove"};
extern const char* STR_VERSION_NUMBER[5] =	{"Version number", "Versjon nummer", "Remove", "Remove", "Remove"};
extern const char* STR_BUILD_NUMBER[5] =	{"Build number", "Utgave-nummer", "Remove", "Remove", "Remove"};

extern int INT_LANGUAGE =					0;
extern int INT_YEAR = 						2000;
extern int INT_MONTH =						1;
extern int INT_DAY =						1;
extern int INT_THEME =						1;
extern int INT_CHARSIZE =					10000;
extern int INT_MAXFILES =					100;

extern int BUILD_NUMBER =					53;

extern bool BOOL_AMERICAN_STYLE =			false;
extern bool BOOL_COLORFUL_CALENDER =		true;

