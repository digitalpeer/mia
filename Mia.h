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


#ifndef MIA_H
#define MIA_H

#include "stdafx.h"
//class MiaBuddyList;


	//this will take a formatted username and eat white space and lowercase it
	CString tocNormalize(CString data);

	//this is the roasting function for the password
	CString tocRoast(const CString &);

	//
	CString tocProcess(const CString &);

	CString stripHtml(CString inputData);

	
	//void tocParseConfigAlias(const CString data, MiaBuddyList *buddy, MiaBuddyList *permit, MiaBuddyList *deny, int *permitStatus);
	void doModalMessage(CString data);




class Mia : public CWinApp
{
	public:
		//initialize the app
		virtual BOOL InitInstance();

		//exit the appa
		virtual int ExitInstance();

		//run the app
		virtual int Run();

		//show the about dialog box
		afx_msg void OnAppAbout();

		
		//void doSignOnDialog();

		CString miaAppPath;

		//the mesage map
		DECLARE_MESSAGE_MAP()
	
	protected:
		//this is a pointer to the main window
		//MiaMainWindow m_mia;
};

#endif
