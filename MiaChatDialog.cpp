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

#include "stdafx.h"
#include "Mia.h"

#include "MiaChatDialog.h"
#include "MiaMainWindow.h"
#include "MiaFileFunc.h"
#include "config.h"


#define IDC_EDIT_VIEW 1009
#define IDC_EDIT_SEND 1009


//this should not be used
MiaChatDialog::MiaChatDialog()
{
	CString initialTitle;
	if (!m_thisBuddyName.IsEmpty())
	{
		initialTitle=m_thisBuddyName + " Instant Message";
	}
	else
	{
		initialTitle=_T("MIA Chat Window");
	}

	//create a brush for the background
	CBrush m_backgroundBrush(RGB(255,255,255));
	
	//register the wnd class
	CString pongWndClass3 = AfxRegisterWndClass((CS_HREDRAW | CS_VREDRAW),
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),
							(HBRUSH) m_backgroundBrush,
							AfxGetApp()->LoadIcon("CHATICON"));

	//create a starting size and position for the window
	CRect test(200,200,600,500);
	
	//actually create the window
	Create(pongWndClass3,initialTitle,WS_OVERLAPPEDWINDOW,test,0,MAKEINTRESOURCE(IDR_MENU_CHAT));

}


MiaChatDialog::MiaChatDialog(CString theName, CString myUsername)
	:m_thisBuddyName(theName),m_myUsername(myUsername)
{
	CString initialTitle;
	if (!m_thisBuddyName.IsEmpty())
	{
		//m_thisBuddyName = theName;
		initialTitle=m_thisBuddyName + " Instant Message";
	}
	else
	{
		initialTitle=_T("MIA Chat Window");
	}

	//create a brush for the background
	CBrush m_backgroundBrush(RGB(255,255,255));
	
	//register the wnd class
	CString pongWndClass2 = AfxRegisterWndClass((CS_HREDRAW | CS_VREDRAW),
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),
							(HBRUSH) m_backgroundBrush,
							AfxGetApp()->LoadIcon("CHATICON"));

	//create a starting size and position for the window
	CRect test(200,200,600,500);
	
	//actually create the window
	Create(pongWndClass2,initialTitle,WS_OVERLAPPEDWINDOW,test,0,MAKEINTRESOURCE(IDR_MENU_CHAT));

	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	

}

CString MiaChatDialog::GetBuddyName()
{
	return m_thisBuddyName;
}

void MiaChatDialog::SetBuddyName(CString theName)
{
	m_thisBuddyName = theName;
}

void MiaChatDialog::UpdateBuddyName(CString theName)
{
	m_thisBuddyName = theName;
	SetWindowText(theName);
}

int MiaChatDialog::OnCreate(LPCREATESTRUCT lpcs)
{

//	SetIcon(m_hIcon, TRUE);			// Set big icon
//	SetIcon(m_hIcon, FALSE);		// Set small icon

	inFlashMode = false;

	CRect clientRectangle;
	GetClientRect(&clientRectangle);

	CRect editRect = clientRectangle;
	CRect sendRect = clientRectangle;

	editRect.bottom = (clientRectangle.bottom * .75)-5;

	
	//m_viewEdit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,editRect,this,IDC_EDIT_VIEW);
	m_viewEdit.Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_READONLY | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_AUTOVSCROLL,editRect,this,IDC_EDIT_VIEW);

	sendRect.top = (clientRectangle.bottom * .75);
	sendRect.bottom = clientRectangle.Height();

	m_sendEdit.Create(/*WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL */ ES_AUTOVSCROLL | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE /*| ES_AUTOVSCROLL | WS_VSCROLL*/,sendRect,this,IDC_EDIT_SEND);

	//m_viewEdit.SetBackgroundColor(FALSE,RGB(255,255,255));

	//m_viewEdit.SetReadOnly(TRUE);

	CFont buddyOffline;
	buddyOffline.CreateFont(
		16,							// nHeight
		0,							// nWidth
		0,							// nEscapement
		0,							// nOrientation
		FW_NORMAL,					// nWeight
		FALSE,						// bItalic
		FALSE,						// bUnderline
		0,							// cStrikeOut
		ANSI_CHARSET,				// nCharSet
		OUT_DEFAULT_PRECIS,			// nOutPrecision
		CLIP_DEFAULT_PRECIS,		// nClipPrecision
		DEFAULT_QUALITY,			// nQuality
		DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
		"Arial");   


	m_viewEdit.SetFont(&buddyOffline);
	m_sendEdit.SetFont(&buddyOffline);

	CString newChatMessage = "Logging Enabled; Started new chat session";
	addSystemMessageToView(&newChatMessage,true);

	
	Invalidate();
	
	return 0;
}

void MiaChatDialog::OnSetFocus( CWnd* pOldWnd )
{

	//if in flash mode, stop the timer
	if (inFlashMode)
	{
		inFlashMode = !inFlashMode;
		KillTimer(25);
		FlashWindow(FALSE);
	}

	//go ahead and give the send focus anytime the window comes in focus
	m_sendEdit.SetFocus();
	
}


void MiaChatDialog::OnPaint( ) 
{ 
    
	CFrameWnd::OnPaint(); 
	
} 

void MiaChatDialog::OnSize(UINT nType, int cx, int cy )
{
	CFrameWnd::OnSize(nType, cx, cy);


	CRect clientRectangle;// = pRect;
	GetClientRect(&clientRectangle);

	CRect editRect = clientRectangle;
	CRect sendRect = clientRectangle;

	editRect.bottom = (clientRectangle.bottom * .75)-5;

	sendRect.top = (clientRectangle.bottom * .75);
	sendRect.bottom = clientRectangle.Height();

	m_sendEdit.MoveWindow(sendRect);
	m_viewEdit.MoveWindow(editRect);
}

void MiaChatDialog::SetOwnerMainWnd(MiaMainWindow* pOwner)
{
	m_pOwner = pOwner;
}

MiaMainWindow* MiaChatDialog::GetOwnerMainWnd()
{
	return m_pOwner;
}

void MiaChatDialog::OnEnterChar() 
{

}

void MiaChatDialog::OnExit()
{
	PostMessage(WM_CLOSE);
}

void MiaChatDialog::OnShowWindow( BOOL bShow, UINT nStatus )
{

	CFrameWnd::OnShowWindow(bShow, nStatus); 

    // retrieve the window size and position settings from the system registry 
    int iVert = AfxGetApp()->GetProfileInt("InitChatWindow","VertPos",0); 
    int iHoriz = AfxGetApp()->GetProfileInt("InitChatWindow","HorizPos",0); 
    int Width = AfxGetApp()->GetProfileInt("InitChatWindow","Width",600);; 
    int Height = AfxGetApp()->GetProfileInt("InitChatWindow","Height",600); 
    // adjust the application's frame size and position 

    SetWindowPos(NULL,iHoriz,iVert,Width,Height, NULL); 
}

void MiaChatDialog::OnClose()
{
	


		//a windows placement structure
    WINDOWPLACEMENT wp; 
	
	//call the get window placement
    GetWindowPlacement(&wp); 

    // write window position and size to the system registry 
    AfxGetApp()->WriteProfileInt("InitChatWindow", 
		"VertPos", 
		wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitChatWindow", 
		"HorizPos", 
		wp.rcNormalPosition.left); 
    AfxGetApp()->WriteProfileInt("InitChatWindow", 
		"Height", 
		wp.rcNormalPosition.bottom - wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitChatWindow", 
		"Width", 
		wp.rcNormalPosition.right - wp.rcNormalPosition.left); 

	m_pOwner->KillBuddyWindow(m_thisBuddyName);

	CFrameWnd::OnClose();
	
	
}

void MiaChatDialog::DoSend()
{
	

	CString* pMessage = new CString;
	m_sendEdit.GetWindowText(*pMessage);

	addMessageToView(pMessage,false,true);

	//now set the send box to nothing
	m_sendEdit.SetWindowText(_T(""));

	MiaMainWindow* pWnd = GetOwnerMainWnd();
			
	//now send the message to the main window to send to server
	pWnd->SendMessage(WM_SENDMESSAGE,(WPARAM)pMessage,(LPARAM)&m_thisBuddyName);


}
	

LRESULT MiaChatDialog::OnReceiveMessage(WPARAM wParam, LPARAM lParam)
{
	CString * pMessage = (CString *) (void *) wParam;
	int isSystemMessage = (int)lParam;

	if (isSystemMessage == 1)
		addSystemMessageToView(pMessage,true);
	else
		addMessageToView(&stripHtml(*pMessage),true,true);

	

	//just got a message, if not in focus then start flash mode
	//get the current window in focus
	//CWnd * currentWndInFocus = (CFrameWnd)GetFocus();

	CFrameWnd* currentWndInFocus = reinterpret_cast<CFrameWnd*>(GetFocus());

	if (!inFlashMode && currentWndInFocus != this)
	{
		inFlashMode = true;
		SetTimer(25,1000,NULL);	//start the timer
	}

	return 0;
}


void MiaChatDialog::addMessageToView(CString * pMessage,bool isIncomming, bool doTimestamp)
{


	
	CHARFORMAT usernameFormat;
	usernameFormat.dwMask = CFM_COLOR | CFM_BOLD;
	usernameFormat.dwEffects = CFE_BOLD;
	//usernameFormat.yHeight = 200;
	if (isIncomming)
		usernameFormat.crTextColor = RGB(0,0,255);
	else
		usernameFormat.crTextColor = RGB(255,0,0);

	
	CString strTemp;
	m_viewEdit.SetSel(-1,-1);				//go to the end point
	m_viewEdit.GetWindowText(strTemp);
	int len = strTemp.GetLength();			//get the last point in the current text
	CString usethisusername;
	if (isIncomming)
		usethisusername = m_thisBuddyName;	//add the username
	else
		usethisusername =m_myUsername;
	
	m_viewEdit.ReplaceSel(usethisusername);	//add the username

	m_viewEdit.SetSel(len,-1);				//select the username just added
	m_viewEdit.SetSelectionCharFormat(usernameFormat);	//format it
	


	CHARFORMAT timeStampFormat;
	timeStampFormat.dwMask = CFM_BOLD | CFM_ITALIC;
	usernameFormat.dwEffects = CFE_ITALIC;
	//timeStampFormat.yHeight = 170;
	//timeStampFormat.crTextColor = RGB(0,0,255);
	//strcpy(timeStampFormat.szFaceName,"Arial");

	CString timeStamp = " (" + GetCurrentTimeStamp() + "): ";
	m_viewEdit.GetWindowText(strTemp);
	len = strTemp.GetLength();			//get the last point in the current text
	m_viewEdit.SetSel(-1,-1);
	m_viewEdit.ReplaceSel(timeStamp);
	m_viewEdit.SetSel(len,-1);
	m_viewEdit.SetSelectionCharFormat(timeStampFormat);



	CHARFORMAT messageFormat;
	messageFormat.dwMask = CFM_COLOR | CFM_BOLD;
	//messageFormat.dwEffects = CFE_ITALIC;
	messageFormat.crTextColor = RGB(0,0,0);
	m_viewEdit.SetSel(-1,-1);
	m_viewEdit.GetWindowText(strTemp);
	len = strTemp.GetLength();			//get the last point in the current text
	m_viewEdit.ReplaceSel(*pMessage + "\r\n");
	m_viewEdit.SetSel(len,-1);
	m_viewEdit.SetSelectionCharFormat(messageFormat);
	m_viewEdit.SetSel(-1,-1);

	CString dir;
	//take and get the current directory of the exe and save it to the member variable
	int nBufferLength = 500;	//500 should be big enough for any file path
	char * lpBuffer = new char[500];
	GetCurrentDirectory(nBufferLength,lpBuffer);	//get the oath into the buffer
	dir = lpBuffer;	//save it to the member variable
	//AfxMessageBox(lpBuffer);	
	delete [] lpBuffer;	//delete the temp buffer

	CreateDirectory(dir + "\\" + MiaConfig::LOGDIR + "\\" + m_thisBuddyName + "\\",0);
	
	//now take and log the message added
	MiaLogToFile(dir + "\\" + MiaConfig::LOGDIR + "\\" + m_thisBuddyName + "\\chatlog.txt", usethisusername + timeStamp + *pMessage);
	
		int min;
	int max;
	GetScrollRange(SB_VERT,&min,&max);
	m_viewEdit.SetScrollPos(SB_VERT,max,true);
	
}

void MiaChatDialog::addSystemMessageToView(CString * pMessage,bool doTimestamp)
{
	CString actualWriteData = "<" + *pMessage + " @ " + GetCurrentTimeStamp() + ">";


	CString dir;
	//take and get the current directory of the exe and save it to the member variable
	int nBufferLength = 500;	//500 should be big enough for any file path
	char * lpBuffer = new char[500];
	GetCurrentDirectory(nBufferLength,lpBuffer);	//get the path into the buffer
	dir = lpBuffer;	//save it to the member variable
	//AfxMessageBox(lpBuffer);	
	delete [] lpBuffer;	//delete the temp buffer

	CreateDirectory(dir + "\\" + MiaConfig::LOGDIR + "\\" + m_thisBuddyName + "\\",0);

	//now take and log the message added
	MiaLogToFile(dir + "\\" + MiaConfig::LOGDIR + "\\" + m_thisBuddyName + "\\chatlog.txt", actualWriteData);


	TRACE("adding system messsage:" + *pMessage + "\r\n");
	CHARFORMAT usernameFormat;
	usernameFormat.dwMask = CFM_COLOR | CFM_BOLD;
	usernameFormat.dwEffects = CFE_BOLD;
	usernameFormat.crTextColor = MiaConfig::BUDDY_IDLE_UNSELECTED_TEXT;
		
	CString strTemp;
	m_viewEdit.SetSel(-1,-1);				//go to the end point
	m_viewEdit.GetWindowText(strTemp);
	int len = strTemp.GetLength();			//get the last point in the current text
	
	m_viewEdit.ReplaceSel(actualWriteData + "\r\n");	//add the message
	
	m_viewEdit.SetSel(len,-1);				//select the username just added
	m_viewEdit.SetSelectionCharFormat(usernameFormat);	//format it
	m_viewEdit.SetSel(-1,-1);

	int min;
	int max;
	GetScrollRange(SB_VERT,&min,&max);
	m_viewEdit.SetScrollPos(SB_VERT,max,true);


}

void MiaChatDialog::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 25)
	{
		FlashWindow(true);
	}
}

CString MiaChatDialog::GetCurrentTimeStamp()
{
	CTime time;
	time = CTime::GetCurrentTime();
	return time.Format("%I:%M:%S");
}



void MiaChatDialog::SaveChatToFile()
{

	TCHAR fileFilters[] = _T("Text files (*.txt)|*.txt|All files (*.*|*.*||");
	CFileDialog fileSaveDlg (TRUE,_T("txt"),_T("*.txt"),
		0,fileFilters);

	if (fileSaveDlg.DoModal() == IDOK)
	{
		CStdioFile saveFile(fileSaveDlg.GetPathName(), CFile::modeWrite | CFile::modeCreate);
		
		CString strTemp;
		m_viewEdit.GetWindowText(strTemp);
		saveFile.WriteString(strTemp);

		saveFile.Close();

	}
}

void MiaChatDialog::LoadChatFromFile()
{
	CString chatData;
	CString buffer;

	TCHAR fileFilters[] = _T("Text files (*.txt)|*.txt|All files (*.*|*.*||");
	CFileDialog fileLoadDlg(TRUE,_T("txt"),_T("*.txt"),
		OFN_FILEMUSTEXIST,fileFilters);

	if (fileLoadDlg.DoModal() == IDOK)
	{	
		CStdioFile loadFile(fileLoadDlg.GetPathName(), CFile::modeRead);

		while(loadFile.ReadString(buffer))
			chatData += buffer + "\n";

		CString strTemp;
		CHARFORMAT messageFormat;
		messageFormat.dwMask = CFM_COLOR | CFM_BOLD;
		messageFormat.crTextColor = RGB(0,100,0);
		m_viewEdit.SetSel(-1,-1);
		m_viewEdit.GetWindowText(strTemp);
		int len = strTemp.GetLength();			//get the last point in the current text
		m_viewEdit.ReplaceSel("\r\n<Loaded Saved Chat " + fileLoadDlg.GetPathName() + ">\r\n" + chatData + "\r\n");
		m_viewEdit.SetSel(len,-1);
		m_viewEdit.SetSelectionCharFormat(messageFormat);
		m_viewEdit.SetSel(-1,-1);

		loadFile.Close();

	}
	
}

BEGIN_MESSAGE_MAP(MiaChatDialog, CFrameWnd)

	ON_WM_PAINT()		//on paint
	ON_COMMAND(ID_CHAT_FILE_EXIT,OnExit)
	ON_WM_SIZE()		//on resize window
	ON_WM_CLOSE()		//close the window
	ON_WM_CREATE()		//create the window
	ON_WM_SETFOCUS()	//get when focus is set on this window
	ON_WM_TIMER()		//this is the timer mainly used for flashing the window
	
	ON_COMMAND(ID_CHAT_FILE_SAVE,SaveChatToFile)
	ON_COMMAND(ID_CHAT_FILE_LOAD,LoadChatFromFile)

	ON_EN_UPDATE(IDC_EDIT_SEND, OnEnterChar)

	ON_WM_SHOWWINDOW()

	ON_MESSAGE(WM_RECEIVEMESSAGE, OnReceiveMessage)

END_MESSAGE_MAP()
