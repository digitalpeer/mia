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

#ifndef MIACHATROOMDIALOG_H
#define MIACHATROOMDIALOG_H

#include "resource.h"

#include "MiaSendTextBox.h"
#include "MiaViewTextBox.h"

class MiaMainWindow;

class MiaChatRoomDialog : public CFrameWnd
{
	public:
		
		//default constructor
		MiaChatRoomDialog();

		MiaChatRoomDialog(CString theName, CString myUsername);

		CString GetChatName();

		//user has pressed enter so do something with the message
		void DoSend();

		//set the owner of this window
		void SetOwnerMainWnd(MiaMainWindow* pOwner);

		void addMessageToView(CString * pMessage,bool isIncomming, bool doTimestamp = false);
		void addSystemMessageToView(CString * pMessage,bool doTimestamp);


	private:

		CString m_myUsername;
		CString m_thisChatName;

		//when this window gets focus give it to the send edit box
		afx_msg void OnSetFocus( CWnd* pOldWnd );

		MiaSendTextBox m_sendEdit;
		MiaViewTextBox m_viewEdit;
		CListBox m_chatRoomList;
		//CRTFStream m_rtfStream;
		
		MiaMainWindow* m_pOwner;

		

		afx_msg void OnPaint();
		
		afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );


		afx_msg void OnExit();

		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
		//afx_msg void OnSizing(UINT fwSide, LPRECT pRect) ;

		afx_msg void OnSize( UINT nType, int cx, int cy );

		afx_msg void OnClose( );

		afx_msg void OnTimer(UINT nIDEvent);
		
		afx_msg LRESULT OnReceiveMessage(WPARAM wParam, LPARAM lParam);
		
		MiaMainWindow* GetOwnerMainWnd();

		bool inFlashMode;

		CString GetCurrentTimeStamp();

		void LoadChatFromFile();
		void SaveChatToFile();

	DECLARE_MESSAGE_MAP()
};

#endif
