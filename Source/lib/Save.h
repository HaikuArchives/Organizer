#ifndef _Save_h_
#define _Save_h_

#include <InterfaceKit.h>
#include <AppKit.h>
#include <StorageKit.h>
#include <SupportKit.h>
#include <TranslationKit.h>
#include <iostream.h>


class _EXPORT MSave	: public BMessage	{
	public:
					MSave(const char* name);
	virtual			~MSave();
	
	status_t		AddString(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								const char* save_text,
								bool replace);
								
	status_t		AddString(const char* filepath, 
								const char* savename, 
								const char* save_text,
								bool replace);
								
	status_t		AddFloat(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								float save_float,
								bool replace);
								
	status_t		AddFloat(const char* filepath, 
								const char* savename, 
								float save_float,
								bool replace);
								
	status_t		AddBool(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								bool save_bool,
								bool replace);
								
	status_t		AddBool(const char* filepath, 
								const char* savename, 
								bool save_bool,
								bool replace);
								
	status_t		AddRect(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								BRect save_rect,
								bool replace);
								
	status_t		AddRect(const char* filepath, 
								const char* savename, 
								BRect save_rect,
								bool replace);
								
	status_t		AddInt32(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								int32 save_int,
								bool replace);
								
	status_t		AddInt32(const char* filepath, 
								const char* savename, 
								int32 save_int,
								bool replace);
								
	status_t		FindString(BPath folderpath,
								const char* filename,
								const char* savename,
								BString* load_to_string,
								const char* default_string);
								
	status_t		FindString(const char* filepath,
								const char* savename,
								BString* load_to_string,
								const char* default_string);
								
	status_t		FindFloat(BPath folderpath,
								const char* filename,
								const char* savename,
								float* load_to_float,
								float default_float);
								
	status_t		FindFloat(const char* filepath,
								const char* savename,
								float* load_to_float,
								float default_float);
	
	status_t		FindBool(BPath folderpath,
								const char* filename,
								const char* savename,
								bool* load_to_bool,
								bool default_bool);
								
	status_t		FindBool(const char* filepath,
								const char* savename,
								bool* load_to_bool,
								bool default_bool);
								
	status_t		FindRect(BPath folderpath,
								const char* filename,
								const char* savename,
								BRect* load_to_rect,
								BRect default_rect);
								
	status_t		FindRect(const char* filepath,
								const char* savename,
								BRect* load_to_rect,
								BRect default_rect);
								
	status_t		FindInt32(BPath folderpath,
								const char* filename,
								const char* savename,
								int32* load_to_int,
								int32 default_int);
								
	status_t		FindInt32(const char* filepath,
								const char* savename,
								int32* load_to_int,
								int32 default_int);
	private:
	BMessage savemessage;
	status_t status;
	BFile file;

};

#endif