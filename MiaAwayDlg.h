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

#if !defined(AFX_MIAAWAYDLG_H__9229B953_7C06_4D15_87E5_7D8BE6A739E5__INCLUDED_)
#define AFX_MIAAWAYDLG_H__9229B953_7C06_4D15_87E5_7D8BE6A739E5__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaAwayDlg.h : header file
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaAwayDlg dialog

class MiaAwayDlg : public CDialog
{
// Construction
public:
	MiaAwayDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MiaAwayDlg)
	enum { IDD = IDD_AWAYMESSAGE };
	CString	m_awayMessage;
	//}}AFX_DATA
	
	bool isAway;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MiaAwayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MiaAwayDlg)
	afx_msg void OnAwaytoggle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAAWAYDLG_H__9229B953_7C06_4D15_87E5_7D8BE6A739E5__INCLUDED_)
