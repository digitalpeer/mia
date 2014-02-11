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

#if !defined(AFX_MIAPROPERTYSHEET_H__EA4402B5_DDAF_490C_A44E_992EF4A5FB0A__INCLUDED_)
#define AFX_MIAPROPERTYSHEET_H__EA4402B5_DDAF_490C_A44E_992EF4A5FB0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaPropertySheet.h : header file
//
#include "stdafx.h"
#include "MiaConfig.h"
#include "MiaPropertyBuddyList.h"
#include "MiaPropertyLogging.h"
#include "MiaPropertyUser.h"
#include "MiaPropertyPageNetwork.h"
#include "MiaPropertyAwayIdle.h"
/////////////////////////////////////////////////////////////////////////////
// MiaPropertySheet

class MiaPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(MiaPropertySheet)

// Construction
public:
	MiaPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	MiaPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

	MiaPropertyPageNetwork m_MiaPropertyPageNetwork;
	MiaPropertyBuddyList m_MiaPropertyBuddyList;
	MiaPropertyUser m_MiaPropertyUser;
	MiaPropertyLogging m_MiaPropertyLogging;
	MiaPropertyAwayIdle m_MiaPropertyAwayIdle;

	//bool m_allowCloseSheet;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MiaPropertySheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MiaPropertySheet();
	void doSaveConfig();
	void doLoadConfig();

	// Generated message map functions
protected:
	//{{AFX_MSG(MiaPropertySheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAPROPERTYSHEET_H__EA4402B5_DDAF_490C_A44E_992EF4A5FB0A__INCLUDED_)
