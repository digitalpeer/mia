#if !defined(AFX_MIAPROPERTYLOGGING_H__53C68F86_D4CB_412A_85D6_DD2C9F0196AB__INCLUDED_)
#define AFX_MIAPROPERTYLOGGING_H__53C68F86_D4CB_412A_85D6_DD2C9F0196AB__INCLUDED_

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

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaPropertyLogging.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaPropertyLogging dialog

class MiaPropertyLogging : public CPropertyPage
{
	DECLARE_DYNCREATE(MiaPropertyLogging)

// Construction
public:
	MiaPropertyLogging();
	~MiaPropertyLogging();

// Dialog Data
	//{{AFX_DATA(MiaPropertyLogging)
	enum { IDD = PROPERTIES_LOGGING };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MiaPropertyLogging)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MiaPropertyLogging)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAPROPERTYLOGGING_H__53C68F86_D4CB_412A_85D6_DD2C9F0196AB__INCLUDED_)
