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

#if !defined(AFX_MIAPROPERTYUSER_H__012925BA_43E1_40C0_8F3F_7EE662F8BD53__INCLUDED_)
#define AFX_MIAPROPERTYUSER_H__012925BA_43E1_40C0_8F3F_7EE662F8BD53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaPropertyUser.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaPropertyUser dialog

class MiaPropertyUser : public CPropertyPage
{
	DECLARE_DYNCREATE(MiaPropertyUser)

// Construction
public:
	MiaPropertyUser();
	~MiaPropertyUser();

// Dialog Data
	//{{AFX_DATA(MiaPropertyUser)
	enum { IDD = PROPERTIES_USER };
	CString	m_tocPassword;
	CString	m_tocUsername;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MiaPropertyUser)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MiaPropertyUser)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAPROPERTYUSER_H__012925BA_43E1_40C0_8F3F_7EE662F8BD53__INCLUDED_)
