
#include "stdafx.h"
#include "resource.h"
#include "config.h"
#include "MiaBuddyListTree.h"


IMPLEMENT_DYNCREATE(MiaBuddyListTree, CTreeCtrl)

BEGIN_MESSAGE_MAP(MiaBuddyListTree, CTreeCtrl)
	ON_WM_LBUTTONDBLCLK()
	//ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()		//right mouse button down
END_MESSAGE_MAP()

void MiaBuddyListTree::OnRButtonDown(UINT nflags,CPoint point)
//void MiaBuddyListTree::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    //CRect rcClient;
    //GetClientRect (&rcClient);

	//int cx = rcClient.Width () / 2;
	//int cy = rcClient.Height () / 2;
	//CRect rcShape (cx - 45, cy - 45, cx + 45, cy + 45);
	
	CPoint pos = point;
	ScreenToClient(&pos);
	

	//CPoint points[3];
	//BOOL bShapeClicked = FALSE;
	//int dx, dy;

	//
	// Hit test the shape.
	//
	/*
	switch (m_nShape) {

	case 0: // Circle
		dx = pos.x - cx;
		dy = pos.y - cy;
		if ((dx * dx) + (dy * dy) <= (45 * 45))
			bShapeClicked = TRUE;
		break;

	case 1: // Triangle
		if (rcShape.PtInRect (pos)) {
	        dx = min (pos.x - rcShape.left, rcShape.right - pos.x);
	        if ((rcShape.bottom - pos.y) < (2 * dx))
	            bShapeClicked = TRUE;
		}
		break;

	case 2: // Square
		if (rcShape.PtInRect (pos))
			bShapeClicked = TRUE;
		break;
		
	}*/

	//
	// Display a context menu if the shape was clicked.
	//
    //if (bShapeClicked) {
        CMenu menu;
        menu.LoadMenu (IDR_MENU5);
        CMenu* pContextMenu = menu.GetSubMenu (0);

        //for (int i=0; i<5; i++)
         //   pContextMenu->ModifyMenu (ID_COLOR_RED + i,
          //      MF_BYCOMMAND | MF_OWNERDRAW, ID_COLOR_RED + i);

        pContextMenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON , pos.x+100, pos.y+100, AfxGetMainWnd());
        //return;
    //}

	//
	// Call the base class if the shape was not clicked.
	//
    //CWnd::OnContextMenu (pWnd, point);
		CTreeCtrl::OnRButtonDown(nflags,point);
}

MiaBuddyListTree::MiaBuddyListTree()
{

	//SendMessage(CCM_SETVERSION,5,0);

}


void MiaBuddyListTree::OnLButtonDblClk( UINT nFlags, CPoint point )
{

	//if this item doesn't have any children then it isn't a group
	//so send the message that a buddy was double clicked
	//i am going to leave it up to the main window to get the currently selected
	//item but this may not be a good idea
	if (!ItemHasChildren(GetSelectedItem( )))
		GetParentFrame()->SendMessage(WM_BUDDYLISTDBLCLICK);

	CTreeCtrl::OnLButtonDblClk(nFlags,point);
}