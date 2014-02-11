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

#if !defined(AFX_MIAPROPERTYBUDDYLIST_H__6EA56C67_DFB3_4FF3_BFDF_D6055B7935CB__INCLUDED_)
#define AFX_MIAPROPERTYBUDDYLIST_H__6EA56C67_DFB3_4FF3_BFDF_D6055B7935CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaPropertyBuddyList.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaPropertyBuddyList dialog

class MiaPropertyBuddyList : public CPropertyPage
{
	DECLARE_DYNCREATE(MiaPropertyBuddyList)

// Construction
public:
	MiaPropertyBuddyList();
	~MiaPropertyBuddyList();

// Dialog Data
	//{{AFX_DATA(MiaPropertyBuddyList)
	enum { IDD = PROPERTIES_BUDDYLIST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MiaPropertyBuddyList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MiaPropertyBuddyList)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAPROPERTYBUDDYLIST_H__6EA56C67_DFB3_4FF3_BFDF_D6055B7935CB__INCLUDED_)
