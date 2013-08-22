#include "Save.h"

//---------------------------------------------------------------
MSave::MSave(const char* name) : BMessage('pref')
{

}

//---------------------------------------------------------------
MSave::~MSave()
{

}

//---------------------------------------------------------------
status_t MSave::AddString(BPath folderpath,
							 const char* filename, 
							 const char* savename, 
							 const char* save_text, 
							 bool replace)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasString(savename) == 0)
	{
	savemessage.AddString(savename, save_text);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceString(savename, save_text);
		}
	}
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}

//---------------------------------------------------------------
status_t MSave::AddString(const char* filepath,
							 const char* savename, 
							 const char* save_text, 
							 bool replace)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasString(savename) == 0)
	{
	savemessage.AddString(savename, save_text);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceString(savename, save_text);
		}
	}
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}

//---------------------------------------------------------------
status_t MSave::AddFloat(BPath folderpath, 
							const char* filename, 
							const char* savename, 
							float save_float, 
							bool replace)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasFloat(savename) == 0)
	{
	savemessage.AddFloat(savename, save_float);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceFloat(savename, save_float);
		}
	}
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}



//---------------------------------------------------------------
status_t MSave::AddFloat(const char* filepath,
							const char* savename, 
							float save_float, 
							bool replace)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasFloat(savename) == 0)
	{
	savemessage.AddFloat(savename, save_float);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceFloat(savename, save_float);
		}
	}
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}



//---------------------------------------------------------------
status_t MSave::AddBool(BPath folderpath, 
							const char* filename, 
							const char* savename, 
							bool save_bool, 
							bool replace)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasBool(savename) == 0)
	{
	savemessage.AddBool(savename, save_bool);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceBool(savename, save_bool);
		}
	}
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}

//---------------------------------------------------------------
status_t MSave::AddBool(const char* filepath,
							const char* savename, 
							bool save_bool, 
							bool replace)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasBool(savename) == 0)
	{
	savemessage.AddBool(savename, save_bool);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceBool(savename, save_bool);
		}
	}
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}

//---------------------------------------------------------------
status_t MSave::AddRect(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								BRect save_rect,
								bool replace)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasRect(savename) == 0)
	{
	savemessage.AddRect(savename, save_rect);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceRect(savename, save_rect);
		}
	}
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}


//---------------------------------------------------------------
status_t MSave::AddRect(const char* filepath,
								const char* savename, 
								BRect save_rect,
								bool replace)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasRect(savename) == 0)
	{
	savemessage.AddRect(savename, save_rect);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceRect(savename, save_rect);
		}
	}
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}

//---------------------------------------------------------------
status_t MSave::AddInt32(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								int32 save_int,
								bool replace)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasInt32(savename) == 0)
	{
	savemessage.AddInt32(savename, save_int);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceInt32(savename, save_int);
		}
	}
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}

//---------------------------------------------------------------
status_t MSave::AddInt32(const char* filepath,
								const char* savename, 
								int32 save_int,
								bool replace)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasInt32(savename) == 0)
	{
	savemessage.AddInt32(savename, save_int);
	}
	else
	{
		if(replace)
		{
		savemessage.ReplaceInt32(savename, save_int);
		}
	}
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return(0);
}

//---------------------------------------------------------------
status_t MSave::FindString(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								BString* load_to_string, 
								const char* default_string)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasString(savename) == 0)
	{
	savemessage.AddString(savename, default_string);
	}
	savemessage.FindString(savename, load_to_string);
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (0);
}

//---------------------------------------------------------------
status_t MSave::FindString(const char* filepath,
								const char* savename, 
								BString* load_to_string, 
								const char* default_string)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasString(savename) == 0)
	{
	savemessage.AddString(savename, default_string);
	}
	savemessage.FindString(savename, load_to_string);
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (0);
}

//---------------------------------------------------------------
status_t MSave::FindFloat(BPath folderpath, 
								const char* filename, 
								const char* savename, 
								float* load_to_float, 
								float default_float)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasFloat(savename) == 0)
	{
	savemessage.AddFloat(savename, default_float);
	}
	savemessage.FindFloat(savename, load_to_float);
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (*load_to_float);
}

//---------------------------------------------------------------
status_t MSave::FindFloat(const char* filepath,
								const char* savename, 
								float* load_to_float, 
								float default_float)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasFloat(savename) == 0)
	{
	savemessage.AddFloat(savename, default_float);
	}
	savemessage.FindFloat(savename, load_to_float);
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (*load_to_float);
}

//---------------------------------------------------------------
status_t MSave::FindBool(BPath folderpath, 
							const char* filename, 
							const char* savename, 
							bool* load_to_bool, 
							bool default_bool)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasBool(savename) == 0)
	{
	savemessage.AddBool(savename, default_bool);
	}
	savemessage.FindBool(savename, load_to_bool);
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return (*load_to_bool);
}

//---------------------------------------------------------------
status_t MSave::FindBool(const char* filepath,
							const char* savename, 
							bool* load_to_bool, 
							bool default_bool)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasBool(savename) == 0)
	{
	savemessage.AddBool(savename, default_bool);
	}
	savemessage.FindBool(savename, load_to_bool);
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	
return (*load_to_bool);
}

//---------------------------------------------------------------
status_t MSave::FindRect(BPath folderpath,
								const char* filename,
								const char* savename,
								BRect* load_to_rect,
								BRect default_rect)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasRect(savename) == 0)
	{
	savemessage.AddRect(savename, default_rect);
	}
	savemessage.FindRect(savename, load_to_rect);
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (0);
//return (load_to_rect);
}


//---------------------------------------------------------------
status_t MSave::FindRect(const char* filepath,
								const char* savename,
								BRect* load_to_rect,
								BRect default_rect)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasRect(savename) == 0)
	{
	savemessage.AddRect(savename, default_rect);
	}
	savemessage.FindRect(savename, load_to_rect);
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (0);
//return (load_to_rect);
}

//---------------------------------------------------------------
status_t MSave::FindInt32(BPath folderpath,
								const char* filename,
								const char* savename,
								int32* load_to_int,
								int32 default_int)
{
folderpath.Append(filename);
status = file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasInt32(savename) == 0)
	{
	savemessage.AddInt32(savename, default_int);
	}
	savemessage.FindInt32(savename, load_to_int);
	
	if (file.SetTo(folderpath.Path(), B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (0);
//return (load_to_rect);
}

//---------------------------------------------------------------
status_t MSave::FindInt32(const char* filepath,
								const char* savename,
								int32* load_to_int,
								int32 default_int)
{
status = file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE);
	if (status == B_OK) 
	{
	status = savemessage.Unflatten(&file);
	}
	
	if (savemessage.HasInt32(savename) == 0)
	{
	savemessage.AddInt32(savename, default_int);
	}
	savemessage.FindInt32(savename, load_to_int);
	
	if (file.SetTo(filepath, B_READ_WRITE | B_CREATE_FILE) == B_OK) 
	{
	savemessage.Flatten(&file);
	}
	/*?*/
return (0);
//return (load_to_rect);
}

