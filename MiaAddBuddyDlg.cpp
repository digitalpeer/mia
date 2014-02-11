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

// MiaAddBuddyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MiaAddBuddyDlg.h"
#include "MiaMainWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaAddBuddyDlg dialog


MiaAddBuddyDlg::MiaAddBuddyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MiaAddBuddyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MiaAddBuddyDlg)
	m_addBuddy = _T("");
//	m_addBuddyGroup = _T("");
	m_group = _T("");
	//}}AFX_DATA_INIT
}


void MiaAddBuddyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaAddBuddyDlg)
	DDX_Text(pDX, IDC_EDIT1, m_addBuddy);
	DDX_CBString(pDX, IDC_COMBO1, m_group);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaAddBuddyDlg, CDialog)
	//{{AFX_MSG_MAP(MiaAddBuddyDlg)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaAddBuddyDlg message handlers

void MiaAddBuddyDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(m_pParentWnd);

	if (!theMainParent->theListBox.addBuddy(m_addBuddy,m_group))
		AfxMessageBox("You entered an invalid buddy name or the buddy already exists");
	else
		DestroyWindow();
}

BOOL MiaAddBuddyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox * thebox = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO1));

	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(m_pParentWnd);
	CList<CString,CString&> theList(10);

	theMainParent->theListBox.getListOfGroups(theList);

	

	POSITION pos = theList.GetHeadPosition();
	for (int i=0;i < theList.GetCount();i++)
	{
		//AfxMessageBox(theList.GetNext(pos));
		thebox->AddString(theList.GetNext(pos));
	}

	
	thebox->SetCurSel(0);	//go ahead and put the first group in the text area

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
