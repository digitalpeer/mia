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

#ifndef MIABUDDYLIST_H
#define MIABUDDYLIST_H

#include "stdafx.h"
class MiaChatDialog;
class MiaBuddy;

class MiaBuddyList : public CTreeCtrl
{
	DECLARE_DYNCREATE(MiaBuddyList)
	private:
		 //MiaNumberTrack * timerIDIndex;
	
	public:

		//BUDDY TREE ICONS
		//these are the icons (by number in the bitmap) for the tree
		static const int ICON_GROUP_DEFAULT;
		static const int ICON_GROUP_DEFAULT_COLLAPSED;
		static const int ICON_BUDDY_DEFAULT;
		static const int ICON_BUDDY_AWAY;
		static const int ICON_BUDDY_SIGNINGON;
		static const int ICON_BUDDY_SIGNINGOFF;
		static const int ICON_BUDDY_IDLE;
		static const int ICON_BUDDY_AOL;
		static const int ICON_BUDDY_AIM;



		//BUDDY STATUS
		static const int BUDDY_STATUS_AWAY;
		static const int BUDDY_STATUS_IDLE;
		static const int BUDDY_STATUS_ONLINE;
		static const int BUDDY_STATUS_OFFLINE;
		static const int BUDDY_TYPE_AOL;
		static const int BUDDY_TYPE_UNCONFIRMED;
		static const int BUDDY_TYPE_NORMAL;
		static const int BUDDY_TYPE_ADMIN;

		static const CString USERCLASSSTRINGS[5];


		MiaBuddyList();		//default constructor
		
		afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
		afx_msg void OnRButtonDown(UINT nflags,CPoint point);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnDestroy();

		
		//BUDDY FUNCTIONS
		HTREEITEM addBuddy(CString name, CString groupName,bool isOnline = false);
		HTREEITEM getBuddyItem(CString name);

		bool addBuddy(MiaBuddy &buddy);
		int getBuddyStatus(CString buddyName);
		CString getBuddyAlias(int num) const;
		void delBuddy(CString name);
		int getBuddyGroup(int num) const;
		void setBuddyStatus(CString buddyName, int status);
		int setBuddyUserClass(CString buddyName, int userClass);
		int setBuddySignonTime(CString buddyName, int time);
		int setBuddyIdleTime(CString buddyName, int time);
		int setBuddyIdleTimeString(CString buddyName, CString time);
		int setBuddyEvil(CString buddyName, int evil);
		int setBuddyLastOn(CString buddyName, int time);
		int setBuddyLastOnString(CString buddyName, CString time);
		int setBuddyGroup(CString buddyName, int group);
		void moveBuddyOffline(CString buddyName);
		void moveBuddyOnline(CString buddyName);

		//update a buddy's data with new data from the server
		void refreshBuddyData(CString thisBuddyName,int newStatus,
				int newEvil,int newsignonTime,int newidleTime,int newbuddyClass);


		//GROUP FUNCTIONS
		HTREEITEM getGroupItem(CString groupName);
		HTREEITEM addGroup(const CString &name);
		
		//this populates a CList of groups for use in populating something like a combobox
		void getListOfGroups(CList<CString,CString&>& theList);
		void delGroup(CString groupName);
		bool renameGroup(const CString &oldname, const CString &newname);
		int getGroupCount();	//count the number of groups
		//count the number of buddies in a group
		int getBuddyCountInGroup(CString groupName, bool OnlineOnly, bool groupNameIsValid);
		int getBuddyCount();
		void updateGroupName(CString groupName,bool onlyShowInCount = false);


		//GENERIC TREE OPERATIONS
		HTREEITEM moveItem(HTREEITEM hItem, HTREEITEM htiNewParent,HTREEITEM htiAfter = TVI_LAST);
		
		//when a buddy signs on, this handles the initial buddy icon
		void buddySignonDisplay(CString buddyName);
		//when a buddy signs off, this handles the initial buddy icon
		void buddySignoffDisplay(CString buddyName);

		
		//this will take the trailing (#,#) off the name for the plain name
		CString normalizeGroupName(CString groupName);

		DECLARE_MESSAGE_MAP()
};


#endif
