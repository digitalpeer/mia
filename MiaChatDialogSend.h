
class MiaChatDialogSend : public CEditView
{
	DECLARE_DYNCREATE(MiaChatDialogSend)

protected:
	MiaChatDialogSend();           // protected constructor used by dynamic creation
	
		
		
public:
	BOOL m_bSendRandomMessages;
	//UINT m_TimerID;
	//MiaMainWindow* GetDocument();
	virtual BOOL DestroyWindow();

protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~MiaChatDialogSend();
	
	
protected:
	
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAutochatter();
	afx_msg void OnUpdateAutochatter(CCmdUI* pCmdUI);
	
	DECLARE_MESSAGE_MAP()
};




