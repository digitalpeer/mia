#include "stdafx.h"
//#include "chatter.h"

//#include "chatdoc.h"
#include "MiaChatDialogView.h"

IMPLEMENT_DYNCREATE(MiaChatDialogView, CEditView)

BEGIN_MESSAGE_MAP(MiaChatDialogView, CEditView)
END_MESSAGE_MAP()


MiaChatDialogView::MiaChatDialogView()
{
}

MiaChatDialogView::~MiaChatDialogView()
{
}


void MiaChatDialogView::OnDraw(CDC* pDC)
{
	//MiaMainWindow* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
}

/*
#ifdef _DEBUG
void MiaChatDialogView::AssertValid() const
{
	CEditView::AssertValid();
}

void MiaChatDialogView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}


CChatDoc* MiaChatDialogView::GetDocument() // non-debug version is inline
{
	return STATIC_DOWNCAST(CChatDoc, m_pDocument);
}
#endif //_DEBUG
*/


BOOL MiaChatDialogView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL ret = CEditView::PreCreateWindow(cs);
	cs.style = AFX_WS_DEFAULT_VIEW | WS_VSCROLL | ES_AUTOHSCROLL |
		ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_READONLY;
	return ret;
}

void MiaChatDialogView::Message(LPCTSTR lpszMessage)
{
	//CString strTemp = lpszMessage;
	//strTemp += _T("\r\n");
	//int len = GetWindowTextLength();
	//GetEditCtrl().SetSel(len,len);
	//GetEditCtrl().ReplaceSel(strTemp);
}
