#ifndef MIABUDDYLISTTREE_H
#define MIABUDDYLISTTREE_H


class MiaBuddyListTree : public CTreeCtrl
{

	public:
		MiaBuddyListTree();
		DECLARE_DYNCREATE(MiaBuddyListTree)


	//CGHCustomDrawDoc* GetDocument();

	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
		//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
		afx_msg void OnRButtonDown(UINT nflags,CPoint point);

		DECLARE_MESSAGE_MAP()	//declare message map . . .
};


#endif
