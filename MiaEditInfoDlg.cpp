
// MiaEditInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "config.h"
#include "MiaEditInfoDlg.h"
#include "MiaMainWindow.h"
#include "MiaFileFunc.h"
#include "MiaConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaEditInfoDlg dialog


MiaEditInfoDlg::MiaEditInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MiaEditInfoDlg::IDD, pParent)
{
	m_mainWindow = pParent;
	//{{AFX_DATA_INIT(MiaEditInfoDlg)
	m_infoData = _T("");
	//}}AFX_DATA_INIT
}




int MiaEditInfoDlg::OnCreate(LPCREATESTRUCT lpcs)
{
	CDialog::OnCreate(lpcs);

	SetIcon(AfxGetApp()->LoadIcon("MAINICON"),false);


	
	return 0;
}

void MiaEditInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaEditInfoDlg)
	DDX_Text(pDX, IDC_RICHEDIT1, m_infoData);
	//}}AFX_DATA_MAP
}


void MiaEditInfoDlg::OnClose()
{
	//AfxMessageBox("here");
	CDialog::OnClose();
	m_mainWindow->SendMessage(WM_ONEDITINFODLGDESTROYED,0,0);
}

BEGIN_MESSAGE_MAP(MiaEditInfoDlg, CDialog)
	//{{AFX_MSG_MAP(MiaEditInfoDlg)
	ON_BN_CLICKED(ID_CANCELINFO, OnCancelInfo)
	ON_BN_CLICKED(ID_SAVEINFO, OnSaveInfo)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaEditInfoDlg message handlers

void MiaEditInfoDlg::OnCancelInfo() 
{
	// TODO: Add your control notification handler code here
	//kill this window
	m_mainWindow->SendMessage(WM_ONEDITINFODLGDESTROYED,0,0);
	DestroyWindow();
	
}

void MiaEditInfoDlg::OnSaveInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	MiaMainWindow* theWindow = (MiaMainWindow*)m_mainWindow;
	theWindow->saveUserInfo(m_infoData);
	m_mainWindow->SendMessage(WM_ONEDITINFODLGDESTROYED,0,0);
	DestroyWindow();
}

void MiaEditInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	CWnd * infoEdit = GetDlgItem(IDC_RICHEDIT1);
	m_infoData = MiaLoadFile(MiaConfig::LOCAL_INFO_FILE_PATH);
	infoEdit->SetWindowText(m_infoData);
	
}
