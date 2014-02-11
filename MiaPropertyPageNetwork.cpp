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


// MiaPropertyPageNetwork.cpp : implementation file
//

#include "stdafx.h"
#include "MiaPropertyPageNetwork.h"
#include "MiaMainWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyPageNetwork property page

IMPLEMENT_DYNCREATE(MiaPropertyPageNetwork, CPropertyPage)

MiaPropertyPageNetwork::MiaPropertyPageNetwork() : CPropertyPage(MiaPropertyPageNetwork::IDD)
{
	//{{AFX_DATA_INIT(MiaPropertyPageNetwork)
	m_tocHost = _T("");
	m_tocPort = 0;
	//}}AFX_DATA_INIT
}

MiaPropertyPageNetwork::~MiaPropertyPageNetwork()
{
}

void MiaPropertyPageNetwork::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaPropertyPageNetwork)
	DDX_Text(pDX, IDC_P_TOCHOST, m_tocHost);
	DDX_Text(pDX, IDC_P_TOCPORT, m_tocPort);
	DDV_MinMaxInt(pDX, m_tocPort, 0, 30000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaPropertyPageNetwork, CPropertyPage)
	//{{AFX_MSG_MAP(MiaPropertyPageNetwork)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyPageNetwork message handlers

void MiaPropertyPageNetwork::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(AfxGetMainWnd());
	//UpdateData(true);
	theMainParent->config.m_tocHost = m_tocHost;
	theMainParent->config.m_tocPort = m_tocPort;
	
	CPropertyPage::OnOK();
}
