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

#include "Resource.h"
#include "config.h"
#include "Mia.h"
#include "MiaTOC.h"
#include "MiaMainWindow.h"
#include "MiaChatDialog.h"
#include "MiaDebugWindow.h"
#include "MiaFileFunc.h"

//dialogs
#include "MiaPropertySheet.h"
#include "MiaAboutDlg.h"
#include "MiaInfoDlg.h"
#include "MiaEditInfoDlg.h"
#include "MiaAddGroupDlg.h"
#include "MiaAddBuddyDlg.h"
#include "MiaAwayDlg.h"
#include "MiaChatRoomDlg.h"



//MFC dynamic create
IMPLEMENT_DYNCREATE(MiaMainWindow,CFrameWnd)

//message map for main buddy list window
BEGIN_MESSAGE_MAP(MiaMainWindow, CFrameWnd)

	/////handle menu commands//////
	ON_COMMAND(ID_MIA_EXIT,OnExit)
	ON_COMMAND(ID_MIA_SIGNONSIGNOFF,OnSignOnSignOff)
	ON_COMMAND(ID_MIA_DEBUGWINDOW,OnDebugWindow)
	ON_COMMAND(ID_MIA_LOADLIST,OnLoadList)
	ON_COMMAND(ID_MIA_SAVELIST,OnSaveList)
	ON_COMMAND(ID_MIA_EDITOPTIONS_PREFERENCES,OnShowProperties)
	ON_COMMAND(ID_MIA_MINIMIZEMAINWINDOW,OnMinimizeMainWindow)
	ON_COMMAND(ID_MIA_SHOWMAINWINDOW,OnShowMainWindow)
	ON_COMMAND(ID_MIA_SHOWALLWINDOWS,OnShowAllWindows)
	ON_COMMAND(ID_MIA_MINIMIZEALLWINDOWS,OnMinimizeAllWindows)
	ON_COMMAND(ID_MIA_CLOSEALLWINDOWS,OnCloseAllWindows)
	ON_COMMAND(ID_ABOUT_ABOUTMIA,OnAbout)
	ON_COMMAND(ID_MIA_AWAYMESSAGE,OnAwayMessage)
	ON_COMMAND(ID_OPTIONS_CHANGEPASSWORD,OnChangePassword)
	ON_COMMAND(ID_EDITINFO,OnEditInfo)
	ON_COMMAND(ID_TOP_GETUSERINFO,OnGetUserInfo)
	ON_COMMAND(ID_TOP_COPYBUDDYNAMETOCLIPBOARD,copySelectedNameToClipboard)

	
	//update menu items
	ON_UPDATE_COMMAND_UI(ID_MIA_SIGNONSIGNOFF,OnSignOnSignOffUpdate)
	ON_UPDATE_COMMAND_UI(ID_MIA_STATUS_SIGNON,OnUpdateStatusMenuSignOn)
	ON_UPDATE_COMMAND_UI(ID_MIA_STATUS_SIGNOFF,OnUpdateStatusMenuSignOff)
	ON_UPDATE_COMMAND_UI(ID_MIA_STATUS_AWAY,OnUpdateStatusMenuAway)
	ON_UPDATE_COMMAND_UI(ID_MIA_STATUS_IDLE,OnUpdateStatusMenuIdle)
	ON_UPDATE_COMMAND_UI(ID_TOP_SERVICE,onDoNothing)
	ON_UPDATE_COMMAND_UI(ID_TOP_WARNINGLEVEL,onDoNothing)
	ON_UPDATE_COMMAND_UI(ID_TOP_IDLETIME,onDoNothing)

	/////window messages//////
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()			//on window paint
	ON_WM_CREATE()			//on window create
	ON_WM_SIZE()			//on window resize
	ON_WM_RBUTTONDOWN()		//right mouse button down
	ON_WM_SYSCOMMAND()		//used to get when window is min/maxed/restored

	//MIA user defined message to send a chat message
	//from child wnd to parent wnd
	ON_MESSAGE(WM_SENDMESSAGE, OnSendMessage)
	ON_MESSAGE(WM_BUDDYLISTDBLCLICK, OnListBoxDblClick)
	ON_MESSAGE(WM_ONEDITINFODLGDESTROYED, OnEditInfoDlgDestroyed)

	//left menu buttons
	ON_BN_CLICKED(IDC_MENUBTN_ADDBUDDY, OnAddBuddy)
	ON_BN_CLICKED(IDC_MENUBTN_ADDGROUP, OnAddGroup)
	ON_BN_CLICKED(IDC_MENUBTN_REMOVE, OnRemoveItem)
	ON_BN_CLICKED(IDC_MENUBTN_STATUS, OnStatusButtonMenu)
	ON_BN_CLICKED(IDC_MENUBTN_CLOSEALL, OnCloseAllWindows)
	ON_BN_CLICKED(IDC_MENUBTN_CHATROOM, OnNewChatRoom)
	

END_MESSAGE_MAP()

//default constructor (NEVER USE THIS- POINTLESS)
MiaMainWindow::MiaMainWindow()
{}

//show add buddy window
void MiaMainWindow::OnAddBuddy()
{
	m_addBuddyDlg = new MiaAddBuddyDlg(this);
	m_addBuddyDlg->Create(IDD_ADDBUDDY);
	m_addBuddyDlg->ShowWindow(SW_SHOW);
}

//show add group window
void MiaMainWindow::OnAddGroup()
{
	m_addGroupDlg = new MiaAddGroupDlg(this);
	m_addGroupDlg->Create(IDD_ADDGROUP);
	m_addGroupDlg->ShowWindow(SW_SHOW);
}

//remove an item from the buddy list
void MiaMainWindow::OnRemoveItem()
{
}
	
void MiaMainWindow::OnStatusButtonMenu()
{

	CMenu menu;
	menu.LoadMenu(IDR_MENU_STATUS);

	CRect buttonRect;
	leftMenuButtons[5].GetWindowRect(&buttonRect);
	//CPoint pos = buttonRect.TopLeft();
	CPoint pos = buttonRect.TopLeft();
	pos.y = pos.y + buttonRect.Height();
	//ScreenToClient(&pos);
	//ClientToScreen(&pos);
			
	CMenu* pContextMenu = menu.GetSubMenu (0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON/*TPM_LEFTBUTTON | TPM_RIGHTBUTTON */, pos.x, pos.y, AfxGetMainWnd());

}



//constructor
MiaMainWindow::MiaMainWindow(Mia * newMia) : m_mia(newMia)
{
	m_bAutoMenuEnable =TRUE;

	m_numberOfChatWindows = 0;
	m_numberOfChatRoomWindows = 0;

	m_chatWindows = new MiaChatDialog*[20];
	m_chatRoomWindows = new MiaChatRoomDialog*[20];

	//remember that the debug window is not active
	debugWindowIsActive = false;

	//create a brush for the background
	CBrush m_backgroundBrush(RGB(30,30,30));
	
	//register the wnd class
	CString pongWndClass = AfxRegisterWndClass((CS_HREDRAW | CS_VREDRAW),
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),
							(HBRUSH) m_backgroundBrush,
							AfxGetApp()->LoadIcon("MAINICON"));//IDI_APPLICATION

	//create a starting size and position for the window
	CRect test(0,0,209,600);
	
	//actually create the window
	Create(pongWndClass,_T("MIA Instant Messenger"),WS_EX_TOPMOST | WS_OVERLAPPEDWINDOW,test,0,MAKEINTRESOURCE(IDR_MENU_MAIN));

	//create the system tray icon
	m_SystemTray.Create(0, WM_ICON_NOTIFY, "MIA Instant Messenger", AfxGetApp()->LoadIcon("MAINICON"),IDR_MENU_TRAY,FALSE);

	//m_SystemTray.SetMenuDefaultItem(3, TRUE);

	//this creates an instance of the toc protocol and the contained socket
	//the parameter is this is a parent
	pTOC = new MiaTOC(this,&theListBox);

	//initialize the config and load it for the first time
	config.InitializeConfig();
}


//this just shows the tray icon too
void MiaMainWindow::OnShowIcon() 
{
    m_SystemTray.ShowIcon();
}


//grab a chat message from a child window and send it away
LRESULT MiaMainWindow::OnSendMessage(WPARAM wParam, LPARAM lParam)
{
	//some casting- this is the only way i could find out how to do this
	CString * pMessage = (CString *) (void *) wParam;
	CString * pBuddy = (CString *) (void *) lParam;

	//UpdateStat("IM to " + *pBuddy);

	//now that I have the data just tell the protocol to handle it
	pTOC->sendIM(*pMessage, *pBuddy, false, false);
	
	return 0;
}

//this is a function that draws/positions everything to the left side of the tree control
void MiaMainWindow::drawControls()
{
	static const int BUTTONWIDTH = 50;
	static const int BUTTONHEIGHT = 20;
	CRect clientRectangle;
	GetClientRect(&clientRectangle);
	
	CRect listBoxRect = clientRectangle;
	listBoxRect.bottom = clientRectangle.bottom - 16;
	listBoxRect.left = (clientRectangle.left +  BUTTONWIDTH + 3);
	theListBox.MoveWindow(listBoxRect);

	CRect statusBoxRect = clientRectangle;
	statusBoxRect.top = clientRectangle.bottom - 15;
	statusBoxRect.right = clientRectangle.right - 1;
	statusBoxRect.bottom = clientRectangle.bottom - 1;
	statusBoxRect.left = (clientRectangle.left +  BUTTONWIDTH + 3);
	m_statusEdit.MoveWindow(statusBoxRect);

	


	//this is the start from top set
	CRect buttonRect = clientRectangle;
	buttonRect.left = 1;
	buttonRect.right = BUTTONWIDTH + 1;
	int currentTop = 1;
	for (int x = 0; x <= 3;x++)
	{
		buttonRect.top = currentTop;
		buttonRect.bottom = currentTop + BUTTONHEIGHT;
		leftMenuButtons[x].MoveWindow(buttonRect);
		currentTop = currentTop + BUTTONHEIGHT + 1;
	}

	//this is the start from bottom set
	buttonRect = clientRectangle;
	buttonRect.left = 1;
	buttonRect.right = BUTTONWIDTH + 1;
	int currentBottom = clientRectangle.bottom - 1;
	for (x = 5; x >= 4;x--)
	{
		buttonRect.top = currentBottom - BUTTONHEIGHT;
		buttonRect.bottom = currentBottom;
		leftMenuButtons[x].MoveWindow(buttonRect);
		currentBottom = currentBottom - BUTTONHEIGHT - 1;
	}

	
}

void MiaMainWindow::OnEditInfo()
{
	if (m_editInfoDlg != 0)
	{
		m_editInfoDlg->SetFocus();
	}
	else
	{
		m_editInfoDlg = new MiaEditInfoDlg(this);
		m_editInfoDlg->Create(IDD_EDITINFO);
		m_editInfoDlg->ShowWindow(SW_SHOW);
		
	}
}

LRESULT MiaMainWindow::OnEditInfoDlgDestroyed(WPARAM wParam, LPARAM lParam)
{
	//delete m_editInfoDlg;
	m_editInfoDlg = 0;
	return 0;
}

void MiaMainWindow::OnShowWindow( BOOL bShow, UINT nStatus )
{

	CFrameWnd::OnShowWindow(bShow, nStatus); 

    // retrieve the window size and position settings from the system registry 
    int iVert = AfxGetApp()->GetProfileInt("InitMainWindow","VertPos",0); 
    int iHoriz = AfxGetApp()->GetProfileInt("InitMainWindow","HorizPos",0); 
    int Width = AfxGetApp()->GetProfileInt("InitMainWindow","Width",209);; 
    int Height = AfxGetApp()->GetProfileInt("InitMainWindow","Height",600); 
    // adjust the application's frame size and position 

    SetWindowPos(0,iHoriz,iVert,Width,Height, 0); 
}

//here's how i decided to make this work.  basically you open up the
//dialog and call it's fetchUserInfo.  It will first display a default
//file saying that it is getting the user info, and it will call toc telling it
//to get the info.  When when the toc class receives any info for a user, it
//automatically sends it to any open info dlg
void MiaMainWindow::OnGetUserInfo()
{
	//get who is currently selected in the list and tell toc to get it
	HTREEITEM hItem = theListBox.GetSelectedItem();
	if (hItem != 0/* && m_infoDlg == 0*/)
	{

		m_infoDlg = new MiaInfoDlg(this);
		m_infoDlg->Create(IDD_INFO);
		m_infoDlg->ShowWindow(SW_SHOW);
		CString theName = theListBox.GetItemText(hItem);
		if (theName.IsEmpty())
			AfxMessageBox("empty name");
		//CString theName = "digitalpeer";
		m_infoDlg->fetchUserInfo(theName);
		
	}
		
}

void MiaMainWindow::onDoNothing()
{}

void MiaMainWindow::OnClose()
{

    //a windows placement structure
    WINDOWPLACEMENT wp; 
	
	//call the get window placement
    GetWindowPlacement(&wp); 

    // write window position and size to the system registry 
    AfxGetApp()->WriteProfileInt("InitMainWindow", 
		"VertPos", 
		wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitMainWindow", 
		"HorizPos", 
		wp.rcNormalPosition.left); 
    AfxGetApp()->WriteProfileInt("InitMainWindow", 
		"Height", 
		wp.rcNormalPosition.bottom - wp.rcNormalPosition.top); 
    AfxGetApp()->WriteProfileInt("InitMainWindow", 
		"Width", 
		wp.rcNormalPosition.right - wp.rcNormalPosition.left); 

	//if the debug window is open, then close it
	if (debugWindowIsActive)
	{
		//kill the debug window properly
		debugWindow->PostMessage(WM_QUIT);
	}


    CFrameWnd::OnClose(); 

}

//create the buddy list window and init all the objects etc
//this does a lot because it resets everything to a starting state
int MiaMainWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	//just a nice check to make sure everything created//allocated ok
	CWnd::OnCreate(lpcs);
		
	//config = new MiaConfiguration;
       


	listBoxFont.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial");  



	//get the area of the window
	CRect clientRectangle;
	GetClientRect(&clientRectangle);

	CRect listBoxRect = clientRectangle;

	//listBoxRect.bottom = (clientRectangle.bottom - 100);
	//listBoxRect.top = (clientRectangle.top + 34);
	//listBoxRect.left = (clientRectangle.left + 35);
	//listBoxRect.right = (clientRectangle.right - 25);

	theListBox.Create( /*|| TVS_EDITLABELS |*/ WS_VISIBLE | WS_TABSTOP | WS_CHILD /*| WS_BORDER | LBS_NOTIFY*/
    /*| TVS_LINESATROOT | TVS_HASLINES */
   | TVS_DISABLEDRAGDROP /*& TVS_NOTOOLTIPS & TVS_HASBUTTONS*/,listBoxRect,this,IDC_TREELISTBOX);

	/*WS_CHILD | WS_VISIBLE | LBS_HASSTRINGS | LBS_OWNERDRAWFIXED | LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY*/
	theListBox.SetFont(&listBoxFont,FALSE);

	//theListBox.ResetContent();

	//load the image list for the tree from the resource
	InitImageLists();	
	//set the image list to the tree
	theListBox.SetImageList(&m_imgNormal,TVSIL_NORMAL/*TVSIL_STATE*/);


	//toplogo.Create(_T("logo"), BS_OWNERDRAW |WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
	//	 clientRectangle, this, 2);

	//if (!toplogo.LoadBitmaps(_T("TOPLOGO"), _T("TOPLOGO"), _T("TOPLOGO")))
	//	AfxMessageBox("failed to load logo bitmap");

	leftMenuButtons[0].Create(_T("Buddy"), /*BS_OWNERDRAW*/BS_FLAT|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		 clientRectangle, this, IDC_MENUBTN_ADDBUDDY);

	leftMenuButtons[1].Create(_T("Group"), /*BS_OWNERDRAW*/BS_FLAT|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		 clientRectangle, this, IDC_MENUBTN_ADDGROUP);

	leftMenuButtons[2].Create(_T("Remove"), /*BS_OWNERDRAW*/BS_FLAT|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		 clientRectangle, this, IDC_MENUBTN_REMOVE);
	
	leftMenuButtons[2].EnableWindow(false);

	leftMenuButtons[3].Create(_T("Close All"), /*BS_OWNERDRAW*/BS_FLAT|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		 clientRectangle, this, IDC_MENUBTN_CLOSEALL);

	leftMenuButtons[3].EnableWindow(false);

	leftMenuButtons[4].Create(_T("Room"), /*BS_OWNERDRAW*/BS_FLAT|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		 clientRectangle, this, IDC_MENUBTN_CHATROOM);
	
	leftMenuButtons[5].Create(_T("Status"), /*BS_OWNERDRAW*/BS_FLAT|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		 clientRectangle, this, IDC_MENUBTN_STATUS);

	leftMenuButtons[5].EnableWindow(false);


	m_statusEdit.Create(ES_MULTILINE | ES_AUTOHSCROLL & ES_AUTOVSCROLL & WS_BORDER | WS_TABSTOP | ES_READONLY | WS_EX_STATICEDGE | WS_CHILD|WS_VISIBLE, 
		 clientRectangle, this, IDC_STATUS_EDIT);

	
	
	

	
	// Use 8pt Courier (monospace) default
	if (m_font.CreatePointFont(80, "MS Sans Serif"))
    {
		for (int x = 0; x<=5;x++)
		{
			leftMenuButtons[x].SetFont(&m_font); // set the window font....
		}
		m_statusEdit.SetFont(&m_font); // set the window font....

	}

	//if (!signoffButton.LoadBitmaps(IDB_ADDGROUP, IDB_ADDGROUP, IDB_ADDGROUP))
	//	AfxMessageBox("failed to load bitmaps");

	drawControls();


	COLORREF acolor=RGB(0,0,0);
	theListBox.SetTextColor(acolor);

	debugWindowIsActive = false;
	//OnDebugWindow();

	m_aboutDlg = 0;
	m_editInfoDlg = 0;
	m_infoDlg = 0;
	//m_signonDlg = 0;

	//doSignOnDialog();
	UpdateStat("Welcome to MIA Version 0.01 BETA");

	m_statusEdit.SetWindowText("MIA v0.0.1 (Offline)");

	return 0;

}

//this creates the image list for use in the buddy list control
void MiaMainWindow::InitImageLists()
{

	CBitmap bmp;
	// normal tree images
	m_imgNormal.Create(16,
				 15,
				 TRUE,
				 20,	// number of initial images
				 20);

	ASSERT(m_imgNormal.m_hImageList);

	bmp.LoadBitmap(IDB_BITMAP1);
	m_imgNormal.Add( &bmp, RGB(255,255,255));
	bmp.DeleteObject();
}

//this creates a new debguf window (if it is not already open)
void MiaMainWindow::OnDebugWindow()
{
	if (!debugWindowIsActive)
	{
		debugWindowIsActive = true;	//remember we have no opened a window
		debugWindow = new MiaDebugWindow;	//create a new window
		debugWindow->ShowWindow(SW_SHOW);		//show the window
		debugWindow->SetOwnerMainWnd(this);		//set the owner of the window
		debugWindow->UpdateWindow();			//update the window
	}
}

void MiaMainWindow::KillDebugWindow()
{
	if (debugWindowIsActive)
	{
		debugWindowIsActive = false;
		//delete debugWindow;
		//debugWindow->PostMessage(WM_QUIT);
	}
}

//this takes messaged and sends them to the debug window if it is open
void MiaMainWindow::UpdateDebug(CString message, bool doCarriageReturn,bool isBold)
{
	if (debugWindowIsActive)
		debugWindow->SendMessage(WM_NEWDEBUGMESSAGE,(WPARAM)&message);
}

//this takes messages and sends it to the signon dialog status label
void MiaMainWindow::UpdateStat(CString message)
{
	m_statusEdit.SetWindowText(message);
}


//when the main window is resized, redraw everything to fit nicely
void MiaMainWindow::OnSize(UINT nType, int cx, int cy )
{
	drawControls();
}

//this takes an incomming message and sends it to the right window
void MiaMainWindow::processNewMessage(CString senderUserName, CString message, bool isAutoReply)
{

	MiaChatDialog* theBuddyWindow;
	if(getWindowOfBuddy(theBuddyWindow,tocNormalize(senderUserName)))
	{
		if (isAutoReply)
		{
			CString smessage = "-Auto Response-";
			theBuddyWindow->SendMessage(WM_RECEIVEMESSAGE,(WPARAM)&smessage,(LPARAM)1);
		}
		else if (pTOC->status == MiaTOC::MIA_AWAY)
		{
			pTOC->sendIM(pTOC->currentAwayMessage, senderUserName, true, false);
		}

		theBuddyWindow->SendMessage(WM_RECEIVEMESSAGE,(WPARAM)&message,(LPARAM)0);
	}
	else
	{
		if (isAutoReply)
		{
			CString smessage = "-Auto Response-";
			theBuddyWindow->SendMessage(WM_RECEIVEMESSAGE,(WPARAM)&smessage,(LPARAM)1);
		}
		else if (pTOC->status == MiaTOC::MIA_AWAY)
		{
			pTOC->sendIM(pTOC->currentAwayMessage, senderUserName, true, false);
		}

		theBuddyWindow = CreateBuddyWindow(tocNormalize(senderUserName));
		theBuddyWindow->SendMessage(WM_RECEIVEMESSAGE,(WPARAM)&message,(LPARAM)0);
	}
}

//this takes an SYSTEM MESSAGE and sends it to the right window opening a new one if needed
void MiaMainWindow::processSystemMessage(CString senderUserName, CString message, bool forceNewWindow)
{
	TRACE("in proccesssystemmessage for user " + senderUserName + "\r\n");
	

	//AfxMessageBox("dispatching system messsage");
	MiaChatDialog* theBuddyWindow;
	if(getWindowOfBuddy(theBuddyWindow,senderUserName))
	{		
		TRACE("sending message to window");
		theBuddyWindow->SendMessage(WM_RECEIVEMESSAGE,(WPARAM)&message,(LPARAM)1);
	}
	else if (forceNewWindow)
	{
		TRACE("sending message to window FORCED");
		theBuddyWindow = CreateBuddyWindow(tocNormalize(senderUserName));
		theBuddyWindow->SendMessage(WM_RECEIVEMESSAGE,(WPARAM)&message,(LPARAM)1);
	}
}


//this will set theWindow = the buddy's window
//it returns true if there was an existing window
//or false if you should create one
bool MiaMainWindow::getWindowOfBuddy(MiaChatDialog* &theWindow, CString theBuddyName)
{
	for (int x = 0; x < m_numberOfChatWindows;x++)
	{
		//UpdateDebug("Searching list of windows");
		if (m_chatWindows[x] != 0)
		{
			CString tempName = m_chatWindows[x]->GetBuddyName();
			//AfxMessageBox(tempName);
			if (tempName == theBuddyName)
			{
				//UpdateDebug("Found Window in List");
				theWindow = m_chatWindows[x];
				return TRUE;
			}
		}
	}
	return FALSE;

}

bool MiaMainWindow::getWindowOfChatRoom(MiaChatRoomDialog* &theWindow, CString chatName)
{
	for (int x = 0; x < m_numberOfChatRoomWindows;x++)
	{
		//UpdateDebug("Searching list of windows");
		if (m_chatWindows[x] != 0)
		{
			CString tempName = m_chatRoomWindows[x]->GetChatName();
			//AfxMessageBox(tempName);
			if (tempName == chatName)
			{
				//UpdateDebug("Found Window in List");
				theWindow = m_chatRoomWindows[x];
				return TRUE;
			}
		}
	}
	return FALSE;

}


//this opens a new buddy window
//if the window already exists it sends it a setfocus message
MiaChatDialog* MiaMainWindow::CreateBuddyWindow(CString openBuddyName)
{
	MiaChatDialog* newChatDialog;
		
	if(getWindowOfBuddy(newChatDialog,openBuddyName))
	{
		newChatDialog->SendMessage(WM_SETFOCUS);
		//AfxMessageBox("need to set the focus of window");
	}
	else
	{
		

		newChatDialog = new MiaChatDialog(openBuddyName,pTOC->username);
	
		newChatDialog->ShowWindow(SW_SHOW);

		newChatDialog->SetOwnerMainWnd(this);

		newChatDialog->UpdateWindow();
	
		m_chatWindows[m_numberOfChatWindows] = newChatDialog;

		m_numberOfChatWindows++;

		//UpdateDebug("Number of chat windows has increased");

	}

	return newChatDialog;
}

MiaChatRoomDialog* MiaMainWindow::OnNewChatRoom()
{
	CString chatname = "SomeChatRoom0000001";
	MiaChatRoomDialog* newChatRoomDialog;
		
	if(getWindowOfChatRoom(newChatRoomDialog,chatname))
	{
		newChatRoomDialog->SendMessage(WM_SETFOCUS);
		//AfxMessageBox("need to set the focus of window");
	}
	else
	{
		

		newChatRoomDialog = new MiaChatRoomDialog(chatname,pTOC->username);
	
		newChatRoomDialog->ShowWindow(SW_SHOW);

		newChatRoomDialog->SetOwnerMainWnd(this);

		newChatRoomDialog->UpdateWindow();
	
		m_chatRoomWindows[m_numberOfChatRoomWindows] = newChatRoomDialog;

		m_numberOfChatRoomWindows++;

		//UpdateDebug("Number of chat windows has increased");

	}

	return newChatRoomDialog;
}



void MiaMainWindow::KillBuddyWindow(CString openBuddyName)
{
	for (int x = 0; x < m_numberOfChatWindows;x++)
	{
		//UpdateDebug("Searching list of windows");
		if (m_chatWindows[x] != 0)
		{
			CString tempName = m_chatWindows[x]->GetBuddyName();
			//AfxMessageBox(tempName);
			if (tempName == openBuddyName)
			{
				m_chatWindows[x]=0;
				m_numberOfChatWindows--;
			}
		}
	}

	
}

void MiaMainWindow::KillChatRoomWindow(CString chatName)
{
	for (int x = 0; x < m_numberOfChatRoomWindows;x++)
	{
		//UpdateDebug("Searching list of windows");
		if (m_chatRoomWindows[x] != 0)
		{
			CString tempName = m_chatRoomWindows[x]->GetChatName();
			//AfxMessageBox(tempName);
			if (tempName == chatName)
			{
				m_chatRoomWindows[x]=0;
				m_numberOfChatRoomWindows--;
			}
		}
	}
}

//this handles a double click on the buddy list asking
//to open the buddy's chat window
void MiaMainWindow::OnListBoxDblClick()
{

	CString openBuddyName;
	
	HTREEITEM hItem =theListBox.GetSelectedItem();
	openBuddyName=theListBox.GetItemText(hItem);

	if (openBuddyName.Find("Group") < 0)
		CreateBuddyWindow(openBuddyName);
}

//tell everything on the board to redraw itself
void MiaMainWindow::OnPaint()
{
	//need a paint struct to be able to call beginpaint
	PAINTSTRUCT ps;				
	CDC* pDC = BeginPaint(&ps);	//start painting
	
	//CRect clientRectangle;
	//GetClientRect(&clientRectangle);
	//pDC->SetMapMode(MM_ANISOTROPIC);
	
	//CBrush backgroundBrushB(RGB(28,28,28));
	//pDC->SelectObject(&backgroundBrushB);
	
	//pDC->Rectangle(clientRectangle);
	
	EndPaint(&ps);				//end paint 
	ReleaseDC(pDC);				//release the dc
}



//right mouse button down
void MiaMainWindow::OnRButtonDown(UINT nflags,CPoint point)
{}



//kill application
void MiaMainWindow::OnExit()
{
	PostMessage(WM_QUIT);
}

//the user has asked to go away (please not they are not actually away yet
void MiaMainWindow::OnAwayMessage()
{
	m_awayDlg = new MiaAwayDlg(this);
	m_awayDlg->Create(IDD_AWAYMESSAGE);
	m_awayDlg->ShowWindow(SW_SHOW);
}

//sign on
void MiaMainWindow::OnSignOnSignOff()
{
	if (pTOC->getStatus() == MiaTOC::MIA_OFFLINE)
	{
		UpdateStat("Command to signon received.");
		pTOC->tocConnect();
	}
	else
	{
		UpdateStat("Command to disconnect received.");
		pTOC->doDisconnect();
	}
		
}

void MiaMainWindow::OnUpdateStatusMenuSignOn(CCmdUI* ptr)
{
	if (pTOC->getStatus() != MiaTOC::MIA_OFFLINE)
		ptr->SetCheck();
	else
		ptr->SetCheck(0);
}

void MiaMainWindow::OnUpdateStatusMenuSignOff(CCmdUI* ptr)
{
	if (pTOC->getStatus() == MiaTOC::MIA_OFFLINE)
		ptr->SetCheck();
	else
		ptr->SetCheck(0);
}

void MiaMainWindow::OnUpdateStatusMenuAway(CCmdUI* ptr)
{
	if (pTOC->getStatus() == MiaTOC::MIA_AWAY)
		ptr->SetCheck();
	else
		ptr->SetCheck(0);
}

void MiaMainWindow::OnUpdateStatusMenuIdle(CCmdUI* ptr)
{
	if (pTOC->getStatus() == MiaTOC::MIA_IDLE)
		ptr->SetCheck();
	else
		ptr->SetCheck(0);

	
}



void MiaMainWindow::OnSignOnSignOffUpdate(CCmdUI* ptr)
{
	if (pTOC->getStatus() == MiaTOC::MIA_OFFLINE)
	{
		ptr->SetText("Sign On");
		//pTOC->setMiaStatus(MIA_ONLINE);
		//ptr->m_nID
			//ptr->Enable(true);
	}
	else
	{
		//ptr->Enable(false);
		ptr->SetText("Sign Off");
		//pTOC->setMiaStatus(MiaTOC::MIA_OFFLINE);
		//ptr->SetText
	}

}

void MiaMainWindow::OnSaveList()
{
	pTOC->SaveListToFile(true);
}

void MiaMainWindow::OnLoadList()
{
	//theListBox.SendMessage(TTM_SETMAXTIPWIDTH,0,SHRT_MAX);
	
	pTOC->LoadListFromFile(true);

}

void MiaMainWindow::OnShowProperties()
{
	MiaPropertySheet theSheet("Mia Options & Preferences",this);
	theSheet.DoModal();
}



void MiaMainWindow::OnMinimizeMainWindow()
{
	/*SW_HIDE
	SW_MINIMIZE
	SW_RESTORE
	SW_SHOW
	SW_SHOWMAXIMIZED
	SW_SHOWMINIMIZED
	SW_SHOWMINNOACTIVE
	SW_SHOWNA
	SW_SHOWNOACTIVATE
	SW_SHOWNORMAL*/
	ShowWindow(SW_SHOWMINIMIZED);
}

//this isn't a real maximize, it's a show window basically
void MiaMainWindow::OnShowMainWindow()
{
	ShowWindow(SW_SHOWNORMAL);
	SetFocus();
}

void MiaMainWindow::OnShowAllWindows()
{
	//ShowWindow(SW_SHOWNORMAL);	//show me first
	
	for (int x = 0; x < m_numberOfChatWindows;x++)
	{
		if (m_chatWindows[x] != 0)
		{
			m_chatWindows[x]->ShowWindow(SW_SHOWNORMAL);
		}
	}

	//now loop through every person in the list and show their window
	
}

void MiaMainWindow::OnCloseAllWindows()
{
	//loop through every person in the list and send kill message
	for (int x = 0; x < m_numberOfChatWindows;x++)
	{
		if (m_chatWindows[x] != 0)
		{
			m_chatWindows[x]->DestroyWindow();
			m_chatWindows[x]=0;
		}
	}
}

void MiaMainWindow::OnMinimizeAllWindows()
{
	//loop through every person in the list and send minimize message

	for (int x = 0; x < m_numberOfChatWindows;x++)
	{
		if (m_chatWindows[x] != 0)
		{
			m_chatWindows[x]->ShowWindow(SW_SHOWMINIMIZED);
		}
	}
}


void MiaMainWindow::OnAbout()
{
	m_aboutDlg = new MiaAboutDlg(this);
	m_aboutDlg->Create(IDD_ABOUT);
	m_aboutDlg->ShowWindow(SW_SHOW);
}


/*
http://msdn.microsoft.com/library/en-us/shellcc/platform/commctls/custdraw/custdraw.asp?frame=true#list_tree
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/shellcc/platform/commctls/custdraw/custdraw.asp

I spent hours trying to set the rect (rc) of the text and everything trying to stop
the dang text from getting clipped when I made it bold or larger...then I found this:

For Version 5.0, these two controls may display clipped text if you change the font by
returning CDRF_NEWFONT. This behavior is necessary for backward compatibility with
earlier versions of the common controls. If you want to change the font of a list-view
or tree-view control, you will get better results if you send a CCM_SETVERSION message
with the wParam value set to 5 before adding any items to the control

Here:  http://msdn.microsoft.com/library/default.asp?url=/library/en-us/shellcc/platform/commctls/custdraw/custdraw.asp

However, it still dowsn't work, so the default text is bold.

SendMessage((HWND) hWndControl,(UINT) CCM_SETVERSION,0) 
*/

BOOL MiaMainWindow::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	CFont buddyOnline;
	
	buddyOnline.CreateFont(
   16,                        // nHeight
   0,                         // nWidth
   0,                         // nEscapement
   0,                         // nOrientation
   FW_NORMAL,/*FW_NORMAL*/                 // nWeight
   FALSE,                     // bItalic
   FALSE,                     // bUnderline
   0,                         // cStrikeOut
   ANSI_CHARSET,              // nCharSet
   OUT_DEFAULT_PRECIS,        // nOutPrecision
   CLIP_DEFAULT_PRECIS,       // nClipPrecision
   DEFAULT_QUALITY,           // nQuality
   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
   "Arial");                 // lpszFacename

	CFont buddyOffline;
	buddyOffline.CreateFont(
		16,							// nHeight
		0,							// nWidth
		0,							// nEscapement
		0,							// nOrientation
		FW_NORMAL,					// nWeight
		TRUE,						// bItalic
		FALSE,						// bUnderline
		0,							// cStrikeOut
		ANSI_CHARSET,				// nCharSet
		OUT_DEFAULT_PRECIS,			// nOutPrecision
		CLIP_DEFAULT_PRECIS,		// nClipPrecision
		DEFAULT_QUALITY,			// nQuality
		DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
		"Arial");   

	
	LPNMHDR pNmhdr = (LPNMHDR)lParam;

	switch (pNmhdr->code)
	{
		case NM_CUSTOMDRAW:
		{
			
			LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)lParam;
			
			switch (pCustomDraw->nmcd.dwDrawStage)
			{
				case CDDS_PREPAINT:
					// Need to process this case and set pResult to CDRF_NOTIFYITEMDRAW, 
					// otherwise parent will never receive CDDS_ITEMPREPAINT notification. (GGH) 
					*pResult = CDRF_NOTIFYITEMDRAW;
					return true;

				case CDDS_ITEMPREPAINT:

					MiaBuddy* thisBuddy = (MiaBuddy*)theListBox.GetItemData((HTREEITEM)pCustomDraw->nmcd.dwItemSpec);

					
					switch (pCustomDraw->iLevel)
					{
						// painting all 0-level items blue,
						// and all 1-level items red (GGH)
						case 0:
							if (pCustomDraw->nmcd.uItemState == (CDIS_FOCUS | CDIS_SELECTED)) // selected
							{
								pCustomDraw->clrTextBk = MiaConfig::GROUP_SELECTED_BACKGROUND;
								pCustomDraw->clrText = MiaConfig::GROUP_SELECTED_TEXT;
							}
							else
							{						
								pCustomDraw->clrTextBk = MiaConfig::GROUP_UNSELECTED_BACKGROUND;
								pCustomDraw->clrText = MiaConfig::GROUP_UNSELECTED_TEXT;
							}
								*pResult = CDRF_NEWFONT;
							break;
						case 1:

							if (pCustomDraw->nmcd.uItemState == (CDIS_FOCUS | CDIS_SELECTED)) // selected
							{
								//buddy is offline
								if (thisBuddy->status == MiaBuddyList::BUDDY_STATUS_OFFLINE)
								{
									pCustomDraw->clrTextBk = MiaConfig::BUDDY_OFFLINE_SELECTED_BACKGROUND;
									pCustomDraw->clrText = MiaConfig::BUDDY_OFFLINE_SELECTED_TEXT;
									SelectObject(pCustomDraw->nmcd.hdc, buddyOffline);
								}
								//buddy is online, but idle
								else if (thisBuddy->idleTime != 0)
								{
									pCustomDraw->clrTextBk = MiaConfig::BUDDY_IDLE_SELECTED_BACKGROUND;
									pCustomDraw->clrText = MiaConfig::BUDDY_IDLE_SELECTED_TEXT;
									SelectObject(pCustomDraw->nmcd.hdc, buddyOnline);
								}
								//buddy is just flat out online
								else
								{
									pCustomDraw->clrTextBk = MiaConfig::BUDDY_SELECTED_BACKGROUND;
									pCustomDraw->clrText = MiaConfig::BUDDY_SELECTED_TEXT;
									SelectObject(pCustomDraw->nmcd.hdc, buddyOnline);
								}
							}
							else
							{
								//buddy is offline
								if (thisBuddy->status == MiaBuddyList::BUDDY_STATUS_OFFLINE)
								{
									pCustomDraw->clrTextBk = MiaConfig::BUDDY_OFFLINE_UNSELECTED_BACKGROUND;
									pCustomDraw->clrText = MiaConfig::BUDDY_OFFLINE_UNSELECTED_TEXT;
									SelectObject(pCustomDraw->nmcd.hdc, buddyOffline);
								}
								//buddy is online, but idle
								else if (thisBuddy->idleTime != 0)
								{
									SelectObject(pCustomDraw->nmcd.hdc, buddyOnline);
									pCustomDraw->clrTextBk = MiaConfig::BUDDY_IDLE_UNSELECTED_BACKGROUND;
									pCustomDraw->clrText = MiaConfig::BUDDY_IDLE_UNSELECTED_TEXT;
								}
								//buddy is just flat out online
								else
								{
									pCustomDraw->clrTextBk = MiaConfig::BUDDY_UNSELECTED_BACKGROUND;
									pCustomDraw->clrText = MiaConfig::BUDDY_UNSELECTED_TEXT;
									SelectObject(pCustomDraw->nmcd.hdc, buddyOnline);
								}
							}
							break;
					}
					*pResult = CDRF_NEWFONT;
					return TRUE;
			}
		}
		break;
	}
	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void MiaMainWindow::saveUserInfo(CString data)
{
	pTOC->setUserInfo(data);
}

void MiaMainWindow::setWindowAlwaysOnTop(bool isOnTop)
{
   if (isOnTop)
   {
      SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
   }
   else
   {
      SetWindowPos( &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
   }
}

void MiaMainWindow::copySelectedNameToClipboard()
{
	if (::OpenClipboard(m_hWnd))
	{
		HTREEITEM hitem = theListBox.GetSelectedItem();
		if (hitem != 0)
		{
			CString text = theListBox.GetItemText(hitem);
			::EmptyClipboard();
			HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE,text.GetLength()+1);
			LPSTR pData = (LPSTR)::GlobalLock(hData);
			::lstrcpy(pData,text.GetBuffer(text.GetLength()));
			::GlobalUnlock(hData);

			::SetClipboardData(CF_TEXT,hData);
			::CloseClipboard();
		}
	}
}

void MiaMainWindow::OnChangePassword()
{
	AfxMessageBox("not implimented yet");
}


void MiaMainWindow::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MINIMIZE)
	{	
		ShowWindow(SW_HIDE);
		return;
	}
	else if (nID == SC_RESTORE)
	{
		ShowWindow(SW_SHOW);//show window
		return;
	}
	
	CFrameWnd::OnSysCommand(nID, lParam);
	
}