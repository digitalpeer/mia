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


// MiaPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "MiaPropertySheet.h"
#include "MiaMainWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaPropertySheet

IMPLEMENT_DYNAMIC(MiaPropertySheet, CPropertySheet)

MiaPropertySheet::MiaPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

MiaPropertySheet::MiaPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_MiaPropertyUser);
	AddPage(&m_MiaPropertyPageNetwork);
	AddPage(&m_MiaPropertyBuddyList);
	AddPage(&m_MiaPropertyLogging);
	AddPage(&m_MiaPropertyAwayIdle);

	doLoadConfig();
}

MiaPropertySheet::~MiaPropertySheet()
{
}


BEGIN_MESSAGE_MAP(MiaPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(MiaPropertySheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaPropertySheet message handlers

//http://codeproject.com/property/hacking_the_cpropertyshee.asp

BOOL MiaPropertySheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// allow message map override
    if (CWnd::OnCommand (wParam, lParam))
        return TRUE;
   
    // crack message parameters
    UINT nID = LOWORD(wParam);
    HWND hWndCtrl = (HWND)lParam;
    int nCode = HIWORD(wParam);
   
    // set m_nModalResult to ID of button, whenever button is clicked
    if (hWndCtrl != NULL && nCode == BN_CLICKED)
    {
        if (::SendMessage(hWndCtrl, WM_GETDLGCODE, 0, 0) &
            (DLGC_BUTTON|DLGC_DEFPUSHBUTTON))
        {
            LONG lStyle = ::GetWindowLong(hWndCtrl, GWL_STYLE) & 0x0F;
            if (lStyle == BS_PUSHBUTTON || lStyle == BS_DEFPUSHBUTTON ||
                lStyle == BS_USERBUTTON || lStyle == BS_OWNERDRAW)
            {
                if (nID == IDOK)
                {
                    //if (m_allowCloseSheet)
                    //{
                        // do whatever you want before closing the property page
						//AfxMessageBox("saving");
						doSaveConfig();
                        // You dont have to assign nID to m_nModalResult. If you want to
                        // return IDOK or IDCANCEL instead of the default return value,
                        // you can do it by assigning IDOK or IDCANCEL to m_nModalResult
                        m_nModalResult = nID;
                    //}
                    //else
                    //{
                        // do whatever you want.
                     //   return TRUE;
                    //}
                }
                else if (nID == ID_APPLY_NOW)
                {
                    //if (m_allowCloseSheet)
                    //{
                        // do whatever you want before closing the property page
                       
                        // You dont have to assign nID to m_nModalResult. If you want to
                        // return IDOK or IDCANCEL instead of the default return value,
                        // you can do it by assigning IDOK or IDCANCEL to m_nModalResult
                        m_nModalResult = nID;
                    //}
                    //else
                    //{
                        // do whatever you want.
                    //   return TRUE;
                    //}
                }
                else if (nID == IDCANCEL)
                {
                    //if (m_allowCloseSheet)
                    //{
                        // do whatever you want before closing the property page

                        // You dont have to assign nID to m_nModalResult. If you want to
                        // return IDOK or IDCANCEL instead of the default return value,
                        // you can do it by assigning IDOK or IDCANCEL to m_nModalResult
                        m_nModalResult = nID;
                    //}
                    //else
                    //{
                        // do whatever you want.
                    //    return TRUE;
                    //}
                }
            }
        }
    }
    return FALSE;
}

//http://codeproject.com/property/hacking_the_cpropertyshee.asp

BOOL MiaPropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	

    int ids [] = {IDOK, IDCANCEL};//, ID_APPLY_NOW, IDHELP };
   
    // Hide Apply and Help buttons
    CWnd *pWnd = GetDlgItem (ID_APPLY_NOW);
    pWnd->ShowWindow (FALSE);
    pWnd = GetDlgItem (IDHELP);
    pWnd->ShowWindow (FALSE);
   
    CRect rectBtn;
    int nSpacing = 6;        // space between two buttons...

    for( int i =0; i < sizeof(ids)/sizeof(int); i++)
    {
        GetDlgItem (ids [i])->GetWindowRect (rectBtn);
       
        ScreenToClient (&rectBtn);
        int btnWidth = rectBtn.Width();
        rectBtn.left = rectBtn.left + (btnWidth + nSpacing)* 2;
        rectBtn.right = rectBtn.right + (btnWidth + nSpacing)* 2;

        GetDlgItem (ids [i])->MoveWindow(rectBtn);
    }

	 return bResult;
}

void MiaPropertySheet::doSaveConfig()
{
	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(m_pParentWnd);
	theMainParent->config.SaveConfig();
}

void MiaPropertySheet::doLoadConfig()
{
	
	MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(m_pParentWnd);

	//save all the user config
	//AfxMessageBox(theMainParent->config.m_tocUsername);
	m_MiaPropertyUser.m_tocUsername = theMainParent->config.m_tocUsername;
	m_MiaPropertyUser.m_tocPassword = theMainParent->config.m_tocPassword;
	//m_MiaPropertyUser.UpdateData(false);

	//save all the network config
	m_MiaPropertyPageNetwork.m_tocHost = theMainParent->config.m_tocHost;
	m_MiaPropertyPageNetwork.m_tocPort = theMainParent->config.m_tocPort;
	//m_MiaPropertyPageNetwork.UpdateData(false);

	//save all the logging config
	//m_MiaPropertyLogging

	//save all the buddylist config
	//m_MiaPropertyBuddyList

	//delete theMainParent;

}
