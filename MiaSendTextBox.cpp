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


#include "MiaSendtextBox.h"
#include "MiaChatDialog.h"



void MiaSendTextBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	if ((nChar != VK_RETURN) || (nRepCnt != 1) || (::GetKeyState(VK_SHIFT) < 0))
	{
		//lastCharWasEnter = FALSE;
		//AfxMessageBox(nChar);
		CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
		return;
	}
	else
	{

		CString strText;
		GetWindowText(strText);
		if (strText.GetLength() != 0)
		{
		//lastCharWasEnter = TRUE;

		//SetWindowText(_T(""));
		CWnd* tparent = GetOwner();

		MiaChatDialog* pparent = reinterpret_cast<MiaChatDialog*>(tparent);
		
		//if (pparent == 0)
		//	 return;
		
		pparent->DoSend();
		//CEdit::OnChar(nChar, nRepCnt, nFlags);

		//MiaChatDialog* pDoc = STATIC_DOWNCAST(MiaChatDialog, m_pDocument)
		}
	}
}

BEGIN_MESSAGE_MAP(MiaSendTextBox, CRichEditCtrl)

	ON_WM_CHAR()
	//ON_WM_KEYDOWN()

END_MESSAGE_MAP()
