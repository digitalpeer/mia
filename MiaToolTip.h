
#ifndef MIATOOLTIP_H
#define MIATOOLTIP_H

#include "resource.h"
class MiaMainWindow;

class MiaToolTip : public CFrameWnd
{
	public:
		
		//default constructor
		MiaToolTip();

		//set the owner of this window
		void SetOwnerMainWnd(MiaMainWindow* pOwner);

	private:

		CEdit m_debugEdit;
		MiaMainWindow* m_pOwner;

		//void OnEnterChar(); 

		//afx_msg void OnPaint();

		afx_msg void OnExit();

		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
		afx_msg void OnSize( UINT nType, int cx, int cy );

		afx_msg void OnClose( );
		afx_msg void OnSaveDebug();
		afx_msg void OnLoadDebug();

		afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );

		afx_msg LRESULT OnNewDebugMessage(WPARAM wParam, LPARAM lParam);
		
		MiaMainWindow* GetOwnerMainWnd();

	DECLARE_MESSAGE_MAP()
};

#endif
