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

//so your probably wondering how I figured out how to do this...
//after hours of research and trying to get the dang view version of the htmlcontrol to work
//like a regular control, I found this:

//http://www.microsoft.com/MSJ/0100/c++/c++0100.asp

//

#if !defined(AFX_MIAINFODLG_H__BE50E9A7_40B7_44D6_B1A2_B646C4EDC95F__INCLUDED_)
#define AFX_MIAINFODLG_H__BE50E9A7_40B7_44D6_B1A2_B646C4EDC95F__INCLUDED_

#include "htmlctrl.h"
#include "resource.h"
#include "stdafx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MiaInfoDlg dialog

class MiaInfoDlg : public CDialog
{
// Construction
public:
	MiaInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MiaInfoDlg)
	enum { IDD = IDD_INFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

CHtmlCtrl m_page;
void OpenUserInfoFile(CString data);
void fetchUserInfo(CString userName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MiaInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MiaInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAINFODLG_H__BE50E9A7_40B7_44D6_B1A2_B646C4EDC95F__INCLUDED_)
