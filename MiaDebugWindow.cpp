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
#include "MiaDebugWindow.h"
#include "MiaMainWindow.h"
#include "config.h"


MiaDebugWindow::MiaDebugWindow()
{
	CString initialTitle;
	initialTitle=_T("MIA Debug Window");
	

	//create a brush for the background
	CBrush m_backgroundBrush(RGB(255,255,255));
	
	//register the wnd class
	CString debugWndClass = AfxRegisterWndClass((CS_HREDRAW | CS_VREDRAW),
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),
							(HBRUSH) m_backgroundBrush,
							AfxGetApp()->LoadIcon("DEBUG"));

	//create a starting size and position for the window
	CRect test(100,100,800,800);
	
	//actually create the window
	Create(debugWndClass,initialTitle,WS_OVERLAPPEDWINDOW,test,0,MAKEINTRESOURCE(IDR_MENU_DEBUG));

}


int MiaDebugWindow::OnCreate(LPCREATESTRUCT lpcs)
{

	CRect clientRectangle;
	GetClientRect(&clientRectangle);

	m_debugEdit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,clientRectangle,this,IDC_DEBUG_VIEW);

	m_debugEdit.SetReadOnly(TRUE);
	
	Invalidate();
	
	return 0;
}



/*
void MiaDebugWindow::OnPaint( ) 
{ 
    
	CFrameWnd::OnPaint(); 
	
} 
*/

void MiaDebugWindow::OnSize(UINT nType, int cx, int cy )
{
	CFrameWnd::OnSize(nType, cx, cy);

	CRect clientRectangle;// = pRect;
	GetClientRect(&clientRectangle);

	m_debugEdit.MoveWindow(clientRectangle);
}

void MiaDebugWindow::SetOwnerMainWnd(MiaMainWindow* pOwner)
{
	m_pOwner = pOwner;
}

MiaMainWindow* MiaDebugWindow::GetOwnerMainWnd()
{
	return m_pOwner;
}




void MiaDebugWindow::OnExit()
{
	PostMessage(WM_CLOSE);
}


void MiaDebugWindow::OnShowWindow( BOOL bShow, UINT nStatus )
{

	CFrameWnd::OnShowWindow(bShow, nStatus); 

    // retrieve the window size and position settings from the system registry 
    int iVert = AfxGetApp()->GetProfileInt("InitDebugWindow","VertPos",0); 
    int iHoriz = AfxGetApp()->GetProfileInt("InitDebugWindow","HorizPos",0); 
    int Width = AfxGetApp()->GetProfileInt("InitDebugWindow","Width",600);; 
    int Height = AfxGetApp()->GetProfileInt("InitDebugWindow","Height",600); 
    // adjust the application's frame size and position 

    SetWindowPos(NULL,iHoriz,iVert,Width,Height, NULL); 
}


void MiaDebugWindow::OnClose()
{

	m_pOwner->KillDebugWindow();

	//a windows placement structure
    WINDOWPLACEMENT wp; 
	
	//call the get window placement
    GetWindowPlacement(&wp); 

    // write window position and size to the system registry 
    AfxGetApp()->WriteProfileInt("InitDebugWindow", 
		"VertPos", 
		wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitDebugWindow", 
		"HorizPos", 
		wp.rcNormalPosition.left); 
    AfxGetApp()->WriteProfileInt("InitDebugWindow", 
		"Height", 
		wp.rcNormalPosition.bottom - wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitDebugWindow", 
		"Width", 
		wp.rcNormalPosition.right - wp.rcNormalPosition.left); 

	
	
	CFrameWnd::OnClose();
}


	
LRESULT MiaDebugWindow::OnNewDebugMessage(WPARAM wParam, LPARAM lParam)
{
	CString * pMessage = (CString *) (void *) wParam;

	CString strTemp;
	m_debugEdit.GetWindowText(strTemp);
	int len = strTemp.GetLength();
	m_debugEdit.SetSel(len,len);
	//CString theMessage = *pMessage;
	m_debugEdit.ReplaceSel(*pMessage + "\r\n");


	//AfxMessageBox(*pMessage);
	return 0;
}

void MiaDebugWindow::OnSaveDebug()
{
	CStdioFile saveFile(_T("debuglog.txt"), CFile::modeWrite | CFile::modeCreate);
	
	CString buffer;
	m_debugEdit.GetWindowText(buffer);
	saveFile.WriteString(buffer);

	//close the file (don't have to but just makes me feel better)
	saveFile.Close();
}

void MiaDebugWindow::OnLoadDebug()
{
	CString buddyListData;
	CString buffer;
	CStdioFile loadFile(_T("debuglog.txt"), CFile::modeRead);

	while(loadFile.ReadString(buffer))
		buddyListData += buffer + "\n";
		
	loadFile.Close();
	
	m_debugEdit.SetWindowText(buffer);

}

BEGIN_MESSAGE_MAP(MiaDebugWindow, CFrameWnd)


	ON_WM_PAINT()
	ON_COMMAND(ID_DEBUG_EXIT,OnExit)
	ON_COMMAND(ID_SAVE,OnSaveDebug)
	ON_COMMAND(ID_LOAD,OnLoadDebug)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	//ON_WM_SETFOCUS()
	
	//ON_EN_UPDATE(IDC_EDIT_SEND, OnEnterChar)

	ON_MESSAGE(WM_NEWDEBUGMESSAGE, OnNewDebugMessage)

END_MESSAGE_MAP()
