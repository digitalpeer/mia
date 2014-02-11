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

// MiaAddGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MiaAddGroupDlg.h"
#include "MiaMainWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaAddGroupDlg dialog


MiaAddGroupDlg::MiaAddGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MiaAddGroupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MiaAddGroupDlg)
	m_addGroup = _T("");
	//}}AFX_DATA_INIT
}


void MiaAddGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaAddGroupDlg)
	DDX_Text(pDX, IDC_EDIT1, m_addGroup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaAddGroupDlg, CDialog)
	//{{AFX_MSG_MAP(MiaAddGroupDlg)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaAddGroupDlg message handlers

void MiaAddGroupDlg::OnAdd() 
{
	
	// TODO: Add your control notification handler code here
	UpdateData();

	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(m_pParentWnd);

	if (!theMainParent->theListBox.addGroup(m_addGroup))
		AfxMessageBox("You entered an invalid group name or the group already exists");
	else
		DestroyWindow();
		

}
