/*
 *
 * Copyright (C) 2002, Josh Henderson <digitalpeer@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "config.h"       // main symbols
#include "resource.h"       // main symbols
#include "Mia.h"
#include "MiaMainWindow.h"
#include "MiaBuddyList.h"

BOOL Mia::InitInstance()
{

	//http://pscode.com/vb/scripts/ShowCode.asp?txtCodeId=67&lngWId=3&txtForceRefresh=48200216423791857 
	SetRegistryKey("MIAInstantMessenger"); 

	m_pMainWnd = new MiaMainWindow(this);
	
	m_pMainWnd->ShowWindow(SW_SHOW); //m_nCmdShow

	m_pMainWnd->UpdateWindow();

	//initialize rich edit features because MSDN says so
	AfxInitRichEdit(); 

	//initialize sockets
	AfxSocketInit();

	AfxEnableControlContainer();

	//take and get the current directory of the exe and save it to the member variable
	int nBufferLength = 500;	//500 should be big enough for any file path
	char * lpBuffer = new char[500];
	GetCurrentDirectory(nBufferLength,lpBuffer);	//get the oath into the buffer
	miaAppPath = lpBuffer;	//save it to the member variable
	//AfxMessageBox(lpBuffer);	
	delete [] lpBuffer;	//delete the temp buffer

	//create the logs dir
	CreateDirectory(miaAppPath + "\\logs\\",0);
	
	
	return TRUE;
}

int Mia::Run()
{
	return CWinApp::Run();
}

int Mia::ExitInstance()
{
	//save and serialize the settings

	//delete the main window
	delete m_pMainWnd;
	return 0;
}



BEGIN_MESSAGE_MAP(Mia, CWinApp)
	//ON_COMMAND(IDD_ABOUT_ABOUTJPONG, OnAppAbout)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////


Mia theBestMiaAppInstanceEver;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();


	enum { IDD = IDD_ABOUT_ABOUTJPONG};



	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}

void Mia::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////

//this takes and converts a username to a safe lowercase/no space string
CString tocNormalize(CString oldstr)
{
	CString workstr;
	int i = 0;
	while(i < oldstr.GetLength())
	{
		if((oldstr.GetAt(i) >= 'A') && (oldstr.GetAt(i) <= 'Z' ))
		{
			workstr += (oldstr.GetAt(i) + (char)32 );
		}
		else if(oldstr.GetAt(i) != ' ')
		{
			workstr += oldstr.GetAt(i);
		}
		i++;
	}
	return workstr;
}

//roast a password for TOC
CString tocRoast(const CString &oldstr)
{
	const CString tocRoast_string = "Tic/Toc";
	const int tocRoast_length = tocRoast_string.GetLength();

	CString newstr;
	CString workstr;
	unsigned char c;

	newstr = "0x";

	for(unsigned int i = 0; i < (unsigned int)oldstr.GetLength(); i++)
	{
		c = oldstr.GetAt(i) ^ (tocRoast_string.GetAt(i % tocRoast_length));
		workstr.Format("%02x", c);
		newstr += workstr;
	}

	return newstr;
}

void doModalMessage(CString data)
{
	AfxMessageBox(data);
}


//this makes a string (most likely a chat message) safe for the server
CString tocProcess(const CString &oldstr)
{
	/*Arguments
with whitespace characters should be enclosed in quotes.  Dollar signs, 
curly brackets, square brackets, parentheses, quotes, and backslashes 
must all be backslashed whether in quotes or not.*/
	CString newstr = "\"";
	for(unsigned int i = 0; i < (unsigned int)oldstr.GetLength(); i++)
	{
		//switch( (char)(QChar)(oldstr.at(i)) )
		switch(oldstr.GetAt(i))
		{
			case '$':
			case '{':
			case '}':
			case '[':
			case ']':
			case '(':
			case ')':
			case '\'':
			case '"':
			case '\\':
				newstr += '\\';
				// fallthrough
			default:
				newstr += oldstr.GetAt(i);
		}
	}
	newstr += "\"";
	return newstr;
}


//compliments of GAIM source code made MFCish
CString stripHtml(CString inputData)
{
	int i, j, k;
	int visible = 1;
	CString outputData = inputData;

	outputData.Replace("<br>", "\r\n");
	outputData.Replace("<BR>", "\r\n");


	for (i = 0, j = 0; i < outputData.GetLength(); i++)
	{
		if (outputData.GetAt(i) == '<') 
		{
			k = i + 1;
			while (k < outputData.GetLength())
			{
				if (outputData.GetAt(k) == '<')
				{
					visible = 1;
					break;
				}
				if (outputData.GetAt(k) == '>')
				{
					visible = 0;
					break;
				}
				k++;
			}
		}
		else if (outputData.GetAt(i) == '>' && !visible)
		{
			visible = 1;
			continue;
		}
		if (visible)
		{
			outputData.SetAt(j++,outputData.GetAt(i));
		}
	}
	outputData = outputData.Left(j);
	return outputData;
}


