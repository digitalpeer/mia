// MiaPropertyAwayIdle.cpp : implementation file
//

#include "stdafx.h"
#include "MiaPropertyAwayIdle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyAwayIdle property page

IMPLEMENT_DYNCREATE(MiaPropertyAwayIdle, CPropertyPage)

MiaPropertyAwayIdle::MiaPropertyAwayIdle() : CPropertyPage(MiaPropertyAwayIdle::IDD)
{
	//{{AFX_DATA_INIT(MiaPropertyAwayIdle)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

MiaPropertyAwayIdle::~MiaPropertyAwayIdle()
{
}

void MiaPropertyAwayIdle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MiaPropertyAwayIdle)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MiaPropertyAwayIdle, CPropertyPage)
	//{{AFX_MSG_MAP(MiaPropertyAwayIdle)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MiaPropertyAwayIdle message handlers
