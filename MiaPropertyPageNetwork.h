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

#if !defined(AFX_MIAPROPERTYPAGENETWORK_H__3D5C0B3A_73ED_4FAB_9A82_BFE399BD8D6A__INCLUDED_)
#define AFX_MIAPROPERTYPAGENETWORK_H__3D5C0B3A_73ED_4FAB_9A82_BFE399BD8D6A__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaPropertyPageNetwork.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaPropertyPageNetwork dialog

class MiaPropertyPageNetwork : public CPropertyPage
{
	DECLARE_DYNCREATE(MiaPropertyPageNetwork)

// Construction
public:
	MiaPropertyPageNetwork();
	~MiaPropertyPageNetwork();

// Dialog Data
	//{{AFX_DATA(MiaPropertyPageNetwork)
	enum { IDD = PROPERTIES_NETWORK };
	CString	m_tocHost;
	short	m_tocPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MiaPropertyPageNetwork)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MiaPropertyPageNetwork)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAPROPERTYPAGENETWORK_H__3D5C0B3A_73ED_4FAB_9A82_BFE399BD8D6A__INCLUDED_)
