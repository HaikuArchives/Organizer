//-----------------------  Local includes  ----------------------
#include "exportWindow.h"

//----------------------- Global includes  ----------------------


//---------------------------------------------------------------
ExportWindow::ExportWindow(BRect frame, const char* title, uint32 resizeMask, uint32 flags, int Month, int Year)
			 : BWindow(frame, title, B_FLOATING_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL, B_NOT_RESIZABLE)
{
_ExportView = new ExportView(BRect(0, 0, 450, 400),"_AboutView", B_FOLLOW_TOP | B_FOLLOW_LEFT | B_FOLLOW_RIGHT, B_WILL_DRAW, Month, Year);

//MoveTo(300, 300);

AddChild(_ExportView);
fSaveTo.SetTo("/boot/home/");
}

//---------------------------------------------------------------
ExportWindow::~ExportWindow()
{

}

//---------------------------------------------------------------
void ExportWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
	case MSG_EXPORT:
		fMonth = _ExportView->fMonth;
		fYear = _ExportView->fYear;
		fFirstNoteOfTheDay = true;
		TableBGColor1.SetTo("EFEFEF");
		TableBGColor2.SetTo("D1DDEF");
		TableColor.SetTo(TableBGColor1);
		
		Head();
		Title();
		Body();
		MainLoop();
		End();
		Close();
	break;
	case MSG_EXPORT_HTML_FILE:
		be_app->PostMessage(message);
	break;
	case MSG_EXPORT_FILENAME_CHANGED:
		if (!strcmp(_ExportView->mFileNameControl->Text(), ""))
		{
		_ExportView->mExportButton->SetEnabled(false);
		}
		else
		{
		_ExportView->mExportButton->SetEnabled(true);
		}
	break;
	default:
	
	break;
	}
}

//---------------------------------------------------------------
bool ExportWindow::QuitRequested()
{
	Close();
	return(1);
	//return BWindow::Close();
}

//---------------------------------------------------------------
void ExportWindow::Head()
{
fContent.SetTo("<html>\n");
}
	
//---------------------------------------------------------------
void ExportWindow::Title()
{
fContent << "<title>";
	if (_ExportView->mNoteCheckBox->Value())
	{
	fContent << "Notes";
		if (_ExportView->mApointmentCheckBox->Value())
		{
		fContent << " And Apointments";
		}
	}
	else
	{
		if (_ExportView->mApointmentCheckBox->Value())
		{
		fContent << "Apointments";
		}
	}
fContent << " For " << STR_MONTHNAMES[fMonth][INT_LANGUAGE] << "</title>\n";
}
	
//---------------------------------------------------------------
void ExportWindow::Body()
{
fContent << "<body bgcolor=\"#FFFFFF\">\n";
fContent << "<h1>" <<STR_MONTHNAMES[fMonth][INT_LANGUAGE] << " " << fYear << "</h1>\n";
}

//---------------------------------------------------------------
void ExportWindow::MainLoop()
{
BString fFilePath;
BString fFolderPath;
BString fFileName;
BPath Path;
BEntry Entry("/boot/home");
MSave Load("Load");

find_directory(B_SYSTEM_SETTINGS_DIRECTORY, &Path);
fFolderPath.SetTo(Path.Path());
fFolderPath.Append(SAVE_NOTE_PATH);

	for (int a = 1; a <= 31; a++)
	{
	fFileName.SetTo("");
	fFileName << a << "-" << fMonth << fYear << "-";
		for (int b = 1; b <= INT_MAXFILES; b++)
		{
		fFileName << b;
		fFilePath.SetTo(fFolderPath);
		fFilePath << fFileName.String();
		Entry.SetTo(fFilePath.String());
			if (Entry.Exists())
			{
			Load.FindString(fFilePath.String(), SAVE_FILE_TYPE, &fType, "M_ERROR");
				
				if (!strcmp(fType.String(), "Note") || !strcmp(fType.String(), "Apointment"))
				{
					//Add the date if it is the first note/apointment of this day
					if (fFirstNoteOfTheDay)
					{
					fContent << "<table width=450 color=\"#FFFFFF\">\n";
					fContent << "<h2>" << a << "." << fMonth << "-" << fYear << "</h2>\n";
					fFirstNoteOfTheDay = false;
					}
					
					//Change the color
					if (!strcmp(TableColor.String(), TableBGColor1.String()))
					{
					TableColor.SetTo(TableBGColor2);
					}
					else
					{
					TableColor.SetTo(TableBGColor1);
					}	
				}
				
				//Its a note
				if (!strcmp(fType.String(), "Note") && _ExportView->mNoteCheckBox->Value())
				{
				Load.FindString(fFilePath.String(), SAVE_FILE_NOTE, &fNote, "M_ERROR");
				Load.FindString(fFilePath.String(), SAVE_FILE_TITLE, &fTitle, "M_ERROR");
				
				fContent << "<tr><td bgcolor=\"" << TableColor.String() << "\" width=430>\n";
				fContent << "<h4>"<< fTitle.String() << "</h4>";
				fNote.ReplaceAll("\n", "<br>");
				fContent << fNote.String() << "\n";
				fContent << "</tr></td>\n";
				}
				
				//Its an apointment
				if (!strcmp(fType.String(), "Apointment") && _ExportView->mApointmentCheckBox->Value())
				{
				Load.FindString(fFilePath.String(), SAVE_FILE_NOTE, &fNote, "M_ERROR");
				Load.FindString(fFilePath.String(), SAVE_FILE_TITLE, &fTitle, "M_ERROR");
				Load.FindString(fFilePath.String(), SAVE_FILE_TIME, &fTime, "M_ERROR");
				
				fContent << "<tr><td bgcolor=\"" << TableColor.String() << "\" width=430>\n";
				fContent << "<h4>"<< fTitle.String() << "";
				
				tmpString.SetTo(fTime);
				tmpString.Remove(0, tmpString.FindFirst(":") + 1);
					if (tmpString.CountChars() == 1)
					{
					fTime.RemoveLast(tmpString.String());
					fTime.Append("0");
					fTime.Append(tmpString.String());
					}
				fContent << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"<< fTime.String() << "</h4>\n";
				fNote.ReplaceAll("\n", "<br>");
				fContent << fNote.String() << "\n";
				fContent << "</tr></td>\n";
				}
			}
		tmpString.SetTo("");
		tmpString << b;
		fFileName.RemoveLast(tmpString.String());
		}
		if (!fFirstNoteOfTheDay)
		{
		fContent << "</table>\n";
		fContent << "<br>";
		}
	fFirstNoteOfTheDay = true;
	}
}

//---------------------------------------------------------------
void ExportWindow::End()
{
fContent << "</body>\n</html>";
fSaveTo.Append("/");
fSaveTo.Append(_ExportView->mFileNameControl->Text());
FILE* file = fopen(fSaveTo.String(), "w");
cout << fSaveTo.String() << endl;
fprintf(file, fContent.String());
fclose(file);
}

