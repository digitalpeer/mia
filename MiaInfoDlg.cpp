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

// MiaInfoDlg.cpp : implementation file
//

#include "MiaInfoDlg.h"
#include "MiaMainWindow.h"
#include "MiaTOC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaInfoDlg dialog


MiaInfoDlg::MiaInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MiaInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MiaInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MiaInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaInfoDlg, CDialog)
	//{{AFX_MSG_MAP(MiaInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaInfoDlg message handlers

BOOL MiaInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	SetIcon(AfxGetApp()->LoadIcon("MAINICON"),false);

	m_page.CreateFromStatic(IDC_HTMLVIEW, this);

	//m_page.Navigate(_T("file://C:\\info.htm"));//.LoadFromResource(_T("about.htm"));

	return TRUE;
}

//this is just basically an interface to the toc protocol
void MiaInfoDlg::fetchUserInfo(CString userName)
{
	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(m_pParentWnd);
	theMainParent->pTOC->requestUserInfo(userName);
	SetWindowText("User Info for " + userName);
}

void MiaInfoDlg::OpenUserInfoFile(CString data)
{
	CString theURL = "http://64.12.163.213/";
	theURL += data;
	m_page.Navigate(theURL);

	CWnd * infoStatus = GetDlgItem(IDC_GETINFOSTATUS);
	infoStatus->SetWindowText(_T(""));
}