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

#if !defined(AFX_MIAADDBUDDYDLG_H__661B6191_E7EF_41A2_A5F8_EB4CA627BADA__INCLUDED_)
#define AFX_MIAADDBUDDYDLG_H__661B6191_E7EF_41A2_A5F8_EB4CA627BADA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaAddBuddyDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaAddBuddyDlg dialog

class MiaAddBuddyDlg : public CDialog
{
// Construction
public:
	MiaAddBuddyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MiaAddBuddyDlg)
	enum { IDD = IDD_ADDBUDDY };
	CString	m_addBuddy;
	//CComboBox	m_comboGroup;
	CString	m_group;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MiaAddBuddyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MiaAddBuddyDlg)
	afx_msg void OnAdd();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAADDBUDDYDLG_H__661B6191_E7EF_41A2_A5F8_EB4CA627BADA__INCLUDED_)
