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

// MiaPropertyBuddyList.cpp : implementation file
//

#include "stdafx.h"
#include "MiaPropertyBuddyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyBuddyList property page

IMPLEMENT_DYNCREATE(MiaPropertyBuddyList, CPropertyPage)

MiaPropertyBuddyList::MiaPropertyBuddyList() : CPropertyPage(MiaPropertyBuddyList::IDD)
{
	//{{AFX_DATA_INIT(MiaPropertyBuddyList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

MiaPropertyBuddyList::~MiaPropertyBuddyList()
{
}

void MiaPropertyBuddyList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaPropertyBuddyList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaPropertyBuddyList, CPropertyPage)
	//{{AFX_MSG_MAP(MiaPropertyBuddyList)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyBuddyList message handlers
