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

// MiaPropertyUser.cpp : implementation file
//

#include "stdafx.h"
#include "MiaPropertyUser.h"
#include "MiaMainWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyUser property page

IMPLEMENT_DYNCREATE(MiaPropertyUser, CPropertyPage)

MiaPropertyUser::MiaPropertyUser() : CPropertyPage(MiaPropertyUser::IDD)
{
	//{{AFX_DATA_INIT(MiaPropertyUser)
	m_tocPassword = _T("");
	m_tocUsername = _T("");
	//}}AFX_DATA_INIT
}

MiaPropertyUser::~MiaPropertyUser()
{
}

void MiaPropertyUser::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaPropertyUser)
	DDX_Text(pDX, IDC_P_TOCPASSWORD, m_tocPassword);
	DDX_Text(pDX, IDC_P_TOCUSERNAME, m_tocUsername);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaPropertyUser, CPropertyPage)
	//{{AFX_MSG_MAP(MiaPropertyUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyUser message handlers

BOOL MiaPropertyUser::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	//UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MiaPropertyUser::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class

	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(AfxGetMainWnd());

	//save all the user config
	
	theMainParent->config.m_tocUsername = m_tocUsername;
	theMainParent->config.m_tocPassword = m_tocPassword;
	
	CPropertyPage::OnOK();
}
