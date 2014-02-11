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

#include "MiaChatRoomDlg.h"
#include "MiaMainWindow.h"
#include "config.h"


#define IDC_EDIT_VIEW 1009
#define IDC_EDIT_SEND 1009



MiaChatRoomDialog::MiaChatRoomDialog()
{
	CString initialTitle;
	if (!m_thisChatName.IsEmpty())
	{
		initialTitle=m_thisChatName + " Instant Message";
	}
	else
	{
		initialTitle=_T("MIA Chat Room Window");
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

CString MiaChatRoomDialog::GetChatName()
{
	return m_thisChatName;
}

MiaChatRoomDialog::MiaChatRoomDialog(CString theName, CString myUsername)
	:m_thisChatName(theName),m_myUsername(myUsername)
{
	CString initialTitle;
	if (!m_thisChatName.IsEmpty())
	{
		//m_thisBuddyName = theName;
		initialTitle=m_thisChatName + " Instant Message";
	}
	else
	{
		initialTitle=_T("MIA Chat Room Window");
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


int MiaChatRoomDialog::OnCreate(LPCREATESTRUCT lpcs)
{

//	SetIcon(m_hIcon, TRUE);			// Set big icon
//	SetIcon(m_hIcon, FALSE);		// Set small icon

	inFlashMode = false;

	CRect clientRectangle;
	GetClientRect(&clientRectangle);

	CRect editRect = clientRectangle;
	CRect sendRect = clientRectangle;
	CRect listRect = clientRectangle;

	editRect.bottom = (clientRectangle.bottom * .75)-5;
	editRect.right = editRect.right - 150;

	
	//m_viewEdit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,editRect,this,IDC_EDIT_VIEW);
	m_viewEdit.Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_READONLY | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_AUTOVSCROLL,editRect,this,IDC_EDIT_VIEW);

	sendRect.top = (clientRectangle.bottom * .75);
	sendRect.bottom = clientRectangle.Height();

	m_sendEdit.Create(/*WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL */ ES_AUTOVSCROLL | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE /*| ES_AUTOVSCROLL | WS_VSCROLL*/,sendRect,this,IDC_EDIT_SEND);

	listRect.left = listRect.right - 145;
	listRect.bottom = (clientRectangle.bottom * .75)-5;
	m_chatRoomList.Create(WS_CHILD|WS_VISIBLE|LBS_STANDARD|WS_HSCROLL|WS_BORDER,listRect,this,IDC_EDIT_CHATROOMLIST);
	
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

	CString newChatMessage = "Started new chat session";
	addSystemMessageToView(&newChatMessage,true);

	
	Invalidate();
	
	return 0;
}

void MiaChatRoomDialog::OnSetFocus( CWnd* pOldWnd )
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


void MiaChatRoomDialog::OnPaint( ) 
{ 
    
	CFrameWnd::OnPaint(); 
	
} 

void MiaChatRoomDialog::OnSize(UINT nType, int cx, int cy )
{
	CFrameWnd::OnSize(nType, cx, cy);


	CRect clientRectangle;// = pRect;
	GetClientRect(&clientRectangle);

	CRect editRect = clientRectangle;
	CRect sendRect = clientRectangle;
	CRect listRect = clientRectangle;

	editRect.bottom = (clientRectangle.bottom * .75);
	editRect.right = editRect.right - 150;

	sendRect.top = (clientRectangle.bottom * .75);
	sendRect.bottom = clientRectangle.Height();

	listRect.left = listRect.right - 145;
	listRect.bottom = (clientRectangle.bottom * .75)-5;
	
	m_sendEdit.MoveWindow(sendRect);
	m_viewEdit.MoveWindow(editRect);
	m_chatRoomList.MoveWindow(listRect);
}

void MiaChatRoomDialog::SetOwnerMainWnd(MiaMainWindow* pOwner)
{
	m_pOwner = pOwner;
}

MiaMainWindow* MiaChatRoomDialog::GetOwnerMainWnd()
{
	return m_pOwner;
}



//m_bAutoDelete 

void MiaChatRoomDialog::OnExit()
{
	PostMessage(WM_CLOSE);
}

void MiaChatRoomDialog::OnShowWindow( BOOL bShow, UINT nStatus )
{

	CFrameWnd::OnShowWindow(bShow, nStatus); 

    // retrieve the window size and position settings from the system registry 
    int iVert = AfxGetApp()->GetProfileInt("InitChatRoomWindow","VertPos",0); 
    int iHoriz = AfxGetApp()->GetProfileInt("InitChatRoomWindow","HorizPos",0); 
    int Width = AfxGetApp()->GetProfileInt("InitChatRoomWindow","Width",600);; 
    int Height = AfxGetApp()->GetProfileInt("InitChatRoomWindow","Height",600); 
    // adjust the application's frame size and position 

    SetWindowPos(NULL,iHoriz,iVert,Width,Height, NULL); 
}

void MiaChatRoomDialog::OnClose()
{
	


		//a windows placement structure
    WINDOWPLACEMENT wp; 
	
	//call the get window placement
    GetWindowPlacement(&wp); 

    // write window position and size to the system registry 
    AfxGetApp()->WriteProfileInt("InitChatRoomWindow", 
		"VertPos", 
		wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitChatRoomWindow", 
		"HorizPos", 
		wp.rcNormalPosition.left); 
    AfxGetApp()->WriteProfileInt("InitChatRoomWindow", 
		"Height", 
		wp.rcNormalPosition.bottom - wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitChatRoomWindow", 
		"Width", 
		wp.rcNormalPosition.right - wp.rcNormalPosition.left); 

	m_pOwner->KillChatRoomWindow(m_thisChatName);

	CFrameWnd::OnClose();
	
	
}

void MiaChatRoomDialog::DoSend()
{
	

	CString* pMessage = new CString;
	m_sendEdit.GetWindowText(*pMessage);

	addMessageToView(pMessage,false,true);

	//now set the send box to nothing
	m_sendEdit.SetWindowText(_T(""));

	MiaMainWindow* pWnd = GetOwnerMainWnd();
			
	//now send the message to the main window to send to server
	pWnd->SendMessage(WM_SENDMESSAGE,(WPARAM)pMessage,(LPARAM)&m_thisChatName);

}
	

LRESULT MiaChatRoomDialog::OnReceiveMessage(WPARAM wParam, LPARAM lParam)
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


void MiaChatRoomDialog::addMessageToView(CString * pMessage,bool isIncomming, bool doTimestamp)
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
	if (isIncomming)
		m_viewEdit.ReplaceSel(m_thisChatName);	//add the username
	else
		m_viewEdit.ReplaceSel(m_myUsername);	//add the username

	m_viewEdit.SetSel(len,-1);				//select the username just added
	m_viewEdit.SetSelectionCharFormat(usernameFormat);	//format it
	


	CHARFORMAT timeStampFormat;
	timeStampFormat.dwMask = CFM_BOLD | CFM_ITALIC;
	usernameFormat.dwEffects = CFE_ITALIC;
	//timeStampFormat.yHeight = 170;
	//timeStampFormat.crTextColor = RGB(0,0,255);
	//strcpy(timeStampFormat.szFaceName,"Arial");

	
	m_viewEdit.GetWindowText(strTemp);
	len = strTemp.GetLength();			//get the last point in the current text
	m_viewEdit.SetSel(-1,-1);
	m_viewEdit.ReplaceSel(" (" + GetCurrentTimeStamp() + "): ");
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
	
}

void MiaChatRoomDialog::addSystemMessageToView(CString * pMessage,bool doTimestamp)
{

	TRACE("adding system messsage:" + *pMessage + "\r\n");
	CHARFORMAT usernameFormat;
	usernameFormat.dwMask = CFM_COLOR | CFM_BOLD;
	usernameFormat.dwEffects = CFE_BOLD;
	usernameFormat.crTextColor = MiaConfig::BUDDY_IDLE_UNSELECTED_TEXT;
		
	CString strTemp;
	m_viewEdit.SetSel(-1,-1);				//go to the end point
	m_viewEdit.GetWindowText(strTemp);
	int len = strTemp.GetLength();			//get the last point in the current text
	
	m_viewEdit.ReplaceSel("<" + *pMessage + " @ " + GetCurrentTimeStamp() + ">\r\n");	//add the message
	
	m_viewEdit.SetSel(len,-1);				//select the username just added
	m_viewEdit.SetSelectionCharFormat(usernameFormat);	//format it
	m_viewEdit.SetSel(-1,-1);
}

void MiaChatRoomDialog::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 25)
	{
		FlashWindow(true);
	}
}

CString MiaChatRoomDialog::GetCurrentTimeStamp()
{
	CTime time;
	time = CTime::GetCurrentTime();
	return time.Format("%I:%M:%S");
}



void MiaChatRoomDialog::SaveChatToFile()
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

void MiaChatRoomDialog::LoadChatFromFile()
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

		m_viewEdit.SetSel(-1,-1);
		m_viewEdit.ReplaceSel("\r\n<Loaded Saved Chat " + fileLoadDlg.GetPathName() + ">\r\n" + chatData + "\r\n");

		loadFile.Close();

	}
	
}

BEGIN_MESSAGE_MAP(MiaChatRoomDialog, CFrameWnd)

	ON_WM_PAINT()		//on paint
	ON_COMMAND(ID_CHAT_FILE_EXIT,OnExit)
	ON_WM_SIZE()		//on resize window
	ON_WM_CLOSE()		//close the window
	ON_WM_CREATE()		//create the window
	ON_WM_SETFOCUS()	//get when focus is set on this window
	ON_WM_TIMER()		//this is the timer mainly used for flashing the window
	
	ON_COMMAND(ID_CHAT_FILE_SAVE,SaveChatToFile)
	ON_COMMAND(ID_CHAT_FILE_LOAD,LoadChatFromFile)

	ON_WM_SHOWWINDOW()

	ON_MESSAGE(WM_RECEIVEMESSAGE, OnReceiveMessage)

END_MESSAGE_MAP()
