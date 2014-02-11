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

// MiaCreateChatRoom.cpp : implementation file
//

#include "stdafx.h"
#include "MiaCreateChatRoom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaCreateChatRoom dialog


MiaCreateChatRoom::MiaCreateChatRoom(CWnd* pParent /*=NULL*/)
	: CDialog(MiaCreateChatRoom::IDD, pParent)
{
	//{{AFX_DATA_INIT(MiaCreateChatRoom)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MiaCreateChatRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaCreateChatRoom)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaCreateChatRoom, CDialog)
	//{{AFX_MSG_MAP(MiaCreateChatRoom)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaCreateChatRoom message handlers
