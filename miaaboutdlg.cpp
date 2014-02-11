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

/////////////////////////////////////////////////////////////////////////////
// MiaAboutDlg dialog


#include "MiaAboutDlg.h"
#include "MiaFileFunc.h"
#include "MiaConfig.h"

MiaAboutDlg::MiaAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MiaAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MiaAboutDlg)
	m_aboutData = _T("");
	//}}AFX_DATA_INIT
}


void MiaAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaAboutDlg)
	DDX_Text(pDX, IDC_EDIT1, m_aboutData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaAboutDlg, CDialog)
	//{{AFX_MSG_MAP(MiaAboutDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaAboutDlg message handlers

void MiaAboutDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	CWnd * aboutEdit = GetDlgItem(IDC_EDIT1);
	m_aboutData = MiaLoadFile(MiaConfig::LOCAL_ABOUTDATA_FILE_PATH);
	//i don't know why but the file load doesn't save \r
	m_aboutData.Replace("\n","\r\n");
	aboutEdit->SetWindowText(m_aboutData);
	
}
