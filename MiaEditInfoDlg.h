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

#if !defined(AFX_MIAEDITINFODLG_H__90029C09_B6E4_4EC4_AC44_D63EB971CD2B__INCLUDED_)
#define AFX_MIAEDITINFODLG_H__90029C09_B6E4_4EC4_AC44_D63EB971CD2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaEditInfoDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaEditInfoDlg dialog

class MiaEditInfoDlg : public CDialog
{
// Construction
public:
	MiaEditInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MiaEditInfoDlg)
	enum { IDD = IDD_EDITINFO };
	CString	m_infoData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MiaEditInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MiaEditInfoDlg)
	afx_msg void OnCancelInfo();
	afx_msg void OnSaveInfo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	CWnd * m_mainWindow;

	afx_msg int OnCreate(LPCREATESTRUCT lpcs);

	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAEDITINFODLG_H__90029C09_B6E4_4EC4_AC44_D63EB971CD2B__INCLUDED_)
