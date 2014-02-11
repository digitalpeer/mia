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
 
 /*
ok, so here is my solution to saving all the preferences and default values and such.
this is basically one big class full of the defaults and the currently active values
for things.  the currently active values are the only thing that gets serialized and
saved when necessary.

to make a long story short, if your anywhere in the program, you should be able to
access this globally defined class that is a member of the app class

i went ahead and saved all the protocol specific stuff with their own class which I
may end up regretting.  this will work for now.
*/

#ifndef MIACONFIG_H
#define MIACONFIG_H

#include "stdafx.h"

class MiaConfig : public CObject
{
	DECLARE_SERIAL(MiaConfig)
	public:
		MiaConfig();
		
		//buddy list colors
		
		enum {GROUP_SELECTED_BACKGROUND = RGB(72,102,149)};
		enum {GROUP_SELECTED_TEXT = RGB(255,255,255)};
		
		enum {GROUP_UNSELECTED_BACKGROUND = RGB(255,255,255)};
		enum {GROUP_UNSELECTED_TEXT = RGB(72,102,149)};

		enum {BUDDY_SELECTED_BACKGROUND = RGB(72,102,149)};
		enum {BUDDY_SELECTED_TEXT = RGB(255,255,255)};
		enum {BUDDY_IDLE_SELECTED_BACKGROUND = RGB(128,128,128)};
		enum {BUDDY_IDLE_SELECTED_TEXT = RGB(255,255,255)};
		enum {BUDDY_OFFLINE_SELECTED_BACKGROUND = RGB(128, 128, 128)};
		enum {BUDDY_OFFLINE_SELECTED_TEXT= RGB(255,255,255)};
				
		enum {BUDDY_UNSELECTED_BACKGROUND = RGB(255, 255, 255)};
		enum {BUDDY_UNSELECTED_TEXT = RGB(0, 0, 0)};
		enum {BUDDY_OFFLINE_UNSELECTED_BACKGROUND = RGB(255,255,255)};
		enum {BUDDY_OFFLINE_UNSELECTED_TEXT= RGB(128,128,128)};
		enum {BUDDY_IDLE_UNSELECTED_BACKGROUND = RGB(255,255,255)};
		enum {BUDDY_IDLE_UNSELECTED_TEXT = RGB(128,128,128)};
		

		
		
		//SOME FILE PATH CONSTANTS
		static const CString LOCAL_INFO_FILE_PATH;
		static const CString LOCAL_ABOUTDATA_FILE_PATH;
		static const CString CONFIG_FILENAME;
		static const CString LOGDIR;

		//static const int SERIALIZE_VERSION;

		//PREFERENCES/PROPERTYSHEET STUFF
		//this is where the property sheet pages save their stuff
		//when they get done saving stuff here they call the serialize function
		CString m_tocUsername;
		CString m_tocPassword;	//please note that this is the plain text password not roasted

		CString m_tocHost;
		short m_tocPort;

		void Serialize(CArchive& ar);

		void InitializeConfig();
		void SaveConfig();

};


#endif

