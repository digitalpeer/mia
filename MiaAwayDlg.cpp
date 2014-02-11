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

// MiaAwayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MiaAwayDlg.h"
#include "MiaMainWindow.h"
#include "MiaTOC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaAwayDlg dialog


MiaAwayDlg::MiaAwayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MiaAwayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MiaAwayDlg)
	m_awayMessage = _T("");
	//}}AFX_DATA_INIT
	
	isAway = false;
}


void MiaAwayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaAwayDlg)
	DDX_Text(pDX, IDC_AWAYMESSAGEEDIT, m_awayMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaAwayDlg, CDialog)
	//{{AFX_MSG_MAP(MiaAwayDlg)
	ON_BN_CLICKED(IDB_AWAYTOGGLE, OnAwaytoggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaAwayDlg message handlers

void MiaAwayDlg::OnAwaytoggle() 
{
	//update the data
	UpdateData();
	//get pointer to parent
	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(m_pParentWnd);
	// TODO: Add your control notification handler code here
	//if away, come back
	if (isAway)
	{
		CWnd * awayEdit = GetDlgItem(IDC_AWAYMESSAGEEDIT);
		awayEdit->EnableWindow(true);

		CWnd * awayButton = GetDlgItem(IDB_AWAYTOGGLE);
		awayButton->SetWindowText("Go Away");

		SetWindowText("Edit Away Message");
		
		theMainParent->pTOC->setAwayMessageOff();
		isAway = !isAway;
	}
	//else go away
	else
	{
		CWnd * awayEdit = GetDlgItem(IDC_AWAYMESSAGEEDIT);
		awayEdit->EnableWindow(false);

		CWnd * awayButton = GetDlgItem(IDB_AWAYTOGGLE);
		awayButton->SetWindowText("Come Back");

		SetWindowText("Currently Away.....");

		theMainParent->pTOC->setAwayMessage(m_awayMessage);
		isAway = !isAway;
	}
	
}
