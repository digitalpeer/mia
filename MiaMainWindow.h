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


#ifndef MIAMAINWINDOW_H
#define MIAMAINWINDOW_H

#include "StdAfx.h"
#include "MiaBuddy.h"
#include "MiaBuddyList.h"
#include "MiaSystemTray.h"
#include "MiaConfig.h"

class Mia;
class MiaChatDialog;
class MiaTOC;
class MiaDebugWindow;
class MiaAboutDlg;
class MiaInfoDlg;
class MiaEditInfoDlg;
class MiaAddBuddyDlg;
class MiaAddGroupDlg;
class MiaAwayDlg;
class MiaChatRoomDialog;

//this is the main buddy list window which handles just about everything in some way
class MiaMainWindow : public CFrameWnd
{
	//wahoo, dyncreate
	DECLARE_DYNCREATE(MiaMainWindow)

	public:

		//this closes the debug window nicely
		void KillDebugWindow();

		//this creates a buddy window
		MiaChatDialog* CreateBuddyWindow(CString openBuddyName);

		MiaChatRoomDialog* OnNewChatRoom();

		//this will get a pointer to the window of a buddy(returns false if it could not find one)
		bool getWindowOfBuddy(MiaChatDialog* &theWindow, CString theBuddyName);

		bool getWindowOfChatRoom(MiaChatRoomDialog* &theWindow, CString chatName);

		//kill a buddy window (after it asks you to kill it)
		void KillBuddyWindow(CString openBuddyName);

		void KillChatRoomWindow(CString chatName);


		//this is the one and only system tray icon (this window handles it's messages)
		CSystemTray m_SystemTray;

		//this is an update stat for the status box on the main window
		void UpdateStat(CString message);
		
		//update debug will send info to the debug windo if it is logged on
		//and it will save the debug to a file if that is enabled
		void UpdateDebug(CString message, bool doCarriageReturn = true, bool isBold = false);

		//the status box on the main window
		CRichEditCtrl m_statusEdit;
		
		
		//DIALOGS
		MiaAboutDlg * m_aboutDlg;		//the about dialog for MIA
		MiaInfoDlg * m_infoDlg;			//the info dialog for reading user info
		MiaEditInfoDlg * m_editInfoDlg;	//edit your own info
		MiaAddBuddyDlg * m_addBuddyDlg;	//add buddy to list
		MiaAddGroupDlg * m_addGroupDlg;	//add group to list
		MiaAwayDlg * m_awayDlg;


		//WINDOWS
		bool debugWindowIsActive;
		MiaDebugWindow* debugWindow;

		MiaChatDialog** m_chatWindows;
		int m_numberOfChatWindows;

		MiaChatRoomDialog** m_chatRoomWindows;
		int m_numberOfChatRoomWindows;


		//PROTOCOLS
		MiaTOC* pTOC;					//TOC protocol
		

		MiaMainWindow();				//default constructor
		MiaMainWindow(Mia* newMia);		//constructor

		//this processes an incoming message (formats it and stuff)
		void processNewMessage(CString senderUserName, CString message, bool isAutoReply);
		
		void processSystemMessage(CString senderUserName, CString message, bool forceNewWindow);

		//send the message to the chat window
		//void dispatchMessage(MiaChatDialog* theWindow,CString message);


		void saveUserInfo(CString data);

		//MESSAGES
		afx_msg void OnPaint();
		afx_msg int OnCreate(LPCREATESTRUCT lpcs);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnClose();
		afx_msg void OnShowProperties();
		afx_msg void OnMinimizeMainWindow();
		afx_msg void OnShowMainWindow();
		afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );
		afx_msg void OnShowAllWindows();
		afx_msg void OnMinimizeAllWindows();
		afx_msg void OnCloseAllWindows();
		afx_msg void OnRButtonDown(UINT nflags,CPoint point);
		afx_msg void OnExit();
		afx_msg	void OnSignOnSignOff();
		afx_msg void OnNewChatWindow();
		afx_msg void OnLoadList();
		afx_msg void OnSaveList();
		afx_msg void OnShowIcon();
		afx_msg void OnHideIcon();
		afx_msg void OnDebugWindow();
		afx_msg void OnChangePassword();
		
		
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

		

		//left menu buttons
		afx_msg void OnAddBuddy();
		afx_msg void OnAddGroup();
		afx_msg void OnRemoveItem();
		afx_msg void OnStatusButtonMenu();

		afx_msg void OnSignOnSignOffUpdate(CCmdUI* ptr);
		afx_msg void OnUpdateStatusMenuSignOn(CCmdUI* ptr);
		afx_msg void OnUpdateStatusMenuSignOff(CCmdUI* ptr);
		afx_msg void OnUpdateStatusMenuAway(CCmdUI* ptr);
		afx_msg void OnUpdateStatusMenuIdle(CCmdUI* ptr);

		//message from a chat window with a message
		afx_msg LRESULT OnSendMessage(WPARAM wParam, LPARAM lParam);

		//destroyed the info dialog so letting parent know
		afx_msg LRESULT OnEditInfoDlgDestroyed(WPARAM wParam, LPARAM lParam);

		virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

		//HANDLE MENU STUFF
		void OnEditInfo();
		void OnGetUserInfo();
		void OnAwayMessage();
		void OnAbout();
		void OnListBoxDblClick();

		//this is the one and only buddy tree
		MiaBuddyList theListBox;

		//this is the DEFAULT fonr for the buddy tree
		CFont listBoxFont;
		
		//this is the image list for the buddy tree		
		CImageList m_imgNormal;

		//inti the images to the buddy tree
		void InitImageLists();

		void drawControls();

		//phone home reference
		Mia* m_mia;

		//these are the buttons on the right side of the buddy list for operations
		CBitmapButton toplogo;

		
		//left menu buttons
		CButton leftMenuButtons[6];

		//default font for something
		CFont m_font;

		//copy buddy name in tree to clipboard (got this out of the book)
		void copySelectedNameToClipboard();
		
		//set the main window always on top
		void setWindowAlwaysOnTop(bool isOnTop = true);

		//the one and only CONFIG class
		MiaConfig config;

		void onDoNothing();
		

		DECLARE_MESSAGE_MAP()	//declare message map . . .
};

#endif
