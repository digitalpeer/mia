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


#ifndef MIADEBUGWINDOW_H
#define MIADEBUGWINDOW_H

#include "resource.h"
class MiaMainWindow;

class MiaDebugWindow : public CFrameWnd
{
	public:
		
		//default constructor
		MiaDebugWindow();

		//set the owner of this window
		void SetOwnerMainWnd(MiaMainWindow* pOwner);

	private:

		CEdit m_debugEdit;
		MiaMainWindow* m_pOwner;

		//void OnEnterChar(); 

		//afx_msg void OnPaint();

		afx_msg void OnExit();

		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
		afx_msg void OnSize( UINT nType, int cx, int cy );

		afx_msg void OnClose( );
		afx_msg void OnSaveDebug();
		afx_msg void OnLoadDebug();

		afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );

		afx_msg LRESULT OnNewDebugMessage(WPARAM wParam, LPARAM lParam);
		
		MiaMainWindow* GetOwnerMainWnd();

	DECLARE_MESSAGE_MAP()
};

#endif
