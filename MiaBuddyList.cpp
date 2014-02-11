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

#include "resource.h"
#include "config.h"
#include "MiaBuddyList.h"
#include "MiaBuddy.h"
#include "MiamainWindow.h"
#include "MiaTOC.h"
#include "MiaNumberTrack.h"

//BUDDY TREE ICONS
const int MiaBuddyList::ICON_GROUP_DEFAULT =		13;
const int MiaBuddyList::ICON_GROUP_DEFAULT_COLLAPSED =		6;
const int MiaBuddyList::ICON_BUDDY_DEFAULT =		5;
const int MiaBuddyList::ICON_BUDDY_AIM =			1;
const int MiaBuddyList::ICON_BUDDY_AWAY =			4;
const int MiaBuddyList::ICON_BUDDY_SIGNINGON =		16;
const int MiaBuddyList::ICON_BUDDY_SIGNINGOFF =		15;
const int MiaBuddyList::ICON_BUDDY_IDLE =			0;
const int MiaBuddyList::ICON_BUDDY_AOL =			3;

//BUDDY STATUS
const int MiaBuddyList::BUDDY_STATUS_AWAY =			0;
const int MiaBuddyList::BUDDY_STATUS_IDLE =			1;
const int MiaBuddyList::BUDDY_STATUS_ONLINE =		2;
const int MiaBuddyList::BUDDY_STATUS_OFFLINE =		3;

const int MiaBuddyList::BUDDY_TYPE_AOL =			1;
const int MiaBuddyList::BUDDY_TYPE_UNCONFIRMED =	2;
const int MiaBuddyList::BUDDY_TYPE_NORMAL =			3;
const int MiaBuddyList::BUDDY_TYPE_ADMIN =			4;

//please note that these strings are the same number as the values above in the array
const CString MiaBuddyList::USERCLASSSTRINGS[5] =
{
	"Unknown",
	"AOL",
	"AIM Trial User",
	"AIM User",
	"AIM Admin",
};



IMPLEMENT_DYNCREATE(MiaBuddyList, CTreeCtrl)

BEGIN_MESSAGE_MAP(MiaBuddyList, CTreeCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()		//right mouse button down
END_MESSAGE_MAP()

MiaBuddyList::MiaBuddyList()
{}


int MiaBuddyList::OnCreate(LPCREATESTRUCT lpcs)
{
	CTreeCtrl::OnCreate(lpcs);

	//timerIDIndex = new MiaNumberTrack(0,10000);

	return 0;
}

HTREEITEM MiaBuddyList::getBuddyItem(CString name)
{
	HTREEITEM answer = 0;
	//get the root group
	HTREEITEM groupItem = GetRootItem();
	while (groupItem != NULL && !answer)	//while there is still something in the tree
	{
	HTREEITEM currentItem = GetNextItem(groupItem,TVGN_CHILD);
	while (currentItem != NULL && !answer)	//while there is still something in the tree
	{
		TVITEM item;
		TCHAR szText[1024];
		//CString szText = name;
		item.hItem = currentItem;
		//only get the text and the handle of the item
		item.mask = TVIF_TEXT | TVIF_HANDLE;	
		item.pszText = szText;
		item.cchTextMax = 1024;

		/*BOOL answer = */
		GetItem(&item);

		CString thisBuddyName = item.pszText;
		if (thisBuddyName == name)
			answer = currentItem ;
		else
			answer = 0;

		//get the next item for the sake of the while loop ending
		currentItem = GetNextItem(currentItem,TVGN_NEXT);
	}
		groupItem = GetNextItem(groupItem,TVGN_NEXT);
	}
	return answer;
}

int MiaBuddyList::getBuddyCount()
{
	int answer = 0;
	//get the root group
	HTREEITEM groupItem = GetRootItem();
	while (groupItem != NULL)	//while there is still something in the tree
	{
	HTREEITEM currentItem = GetNextItem(groupItem,TVGN_CHILD);
	while (currentItem != NULL)	//while there is still something in the tree
	{
		answer++;

		//get the next item for the sake of the while loop ending
		currentItem = GetNextItem(currentItem,TVGN_NEXT);
	}
		groupItem = GetNextItem(groupItem,TVGN_NEXT);
	}
	return answer;
}

HTREEITEM MiaBuddyList::getGroupItem(CString groupName)
{
	groupName = normalizeGroupName(groupName);
	HTREEITEM answer = 0;
	
	HTREEITEM groupItem = GetRootItem()/*(TVI_ROOT, TVGN_NEXT)*/;
	while (groupItem != NULL && !answer)	//while there is still something in the tree
	{
	
		TVITEM item;
		TCHAR szText[1024];
		//CString szText = name;
		item.hItem = groupItem;
		//only get the text and the handle of the item
		item.mask = TVIF_TEXT | TVIF_HANDLE;	
		item.pszText = szText;
		item.cchTextMax = 1024;

		GetItem(&item);

		CString thisGroupName = item.pszText;
		thisGroupName = normalizeGroupName(thisGroupName);
		if (thisGroupName == groupName)
			answer = groupItem;
		
		//get the next item for the sake of the while loop ending
		groupItem = GetNextItem(groupItem,TVGN_NEXT);
	}
	return answer;
}


bool MiaBuddyList::addBuddy(MiaBuddy &buddy)
{
	return true;
}

void MiaBuddyList::moveBuddyOnline(CString buddyName)
{
	//get the current buddy item
	HTREEITEM buddyItem = getBuddyItem(buddyName);
	if (buddyItem == 0)
		AfxMessageBox("could not get buddy in moveing online");
	
	DWORD temp = GetItemData(buddyItem);

	MiaBuddy* thisBuddy = (MiaBuddy*)temp;
	
	CString groupName = thisBuddy->groupName;
	//AfxMessageBox("taking user online from group:" + groupName);
	
	//get the group Item of the new group
	HTREEITEM groupItem = getGroupItem(groupName);

	HTREEITEM movedItem = moveItem(buddyItem,groupItem,TVI_SORT);
	
	
	//this means that the buddy count for the group has changed so update
	//the group count displayed
	updateGroupName(groupName);
	updateGroupName("Offline",true);

	
	HTREEITEM hParent = GetParentItem(movedItem);
		if (hParent != NULL)
			Expand(hParent, TVE_EXPAND);
}

void MiaBuddyList::moveBuddyOffline(CString buddyName)
{
	//AfxMessageBox("hello world");
	//get the current buddy item
	HTREEITEM buddyItem = getBuddyItem(buddyName);

	if (buddyItem == 0)
	{
		AfxMessageBox("could not move buddy offline: " + buddyName);
		return;
	}

	DWORD temp = GetItemData(buddyItem);

	
	
	//get the group Item of the new group
	HTREEITEM groupItem = getGroupItem("Offline");

	HTREEITEM movedItem = moveItem(buddyItem,groupItem,TVI_SORT);

	//HTREEITEM hParent = GetParentItem(movedItem);
	//	if (hParent != NULL)
	//		Expand(hParent, TVE_EXPAND);

	//this means that the buddy count for the group has changed so update
	//the group count displayed
	//get the name of the group the buddy was in
	MiaBuddy* thisBuddy = (MiaBuddy*)temp;
	updateGroupName(thisBuddy->groupName);
	updateGroupName("Offline",true);

}

void MiaBuddyList::updateGroupName(CString groupName, bool onlyShowInCount)
{
	//get the group item
	HTREEITEM groupItem = getGroupItem(groupName);

	CString intToStrTemp;

	//now reset it's text
	CString finalName = groupName;

	if (!onlyShowInCount)
	{
	finalName += " (";
	intToStrTemp.Format("%d",getBuddyCountInGroup(groupName,true,true));
	finalName += intToStrTemp;
	finalName += "/";
	intToStrTemp.Format("%d",getBuddyCountInGroup(groupName,false,true));
	finalName += intToStrTemp;
	finalName += ")";
	}
	else
	{
		finalName += " (";
		intToStrTemp.Format("%d",getBuddyCountInGroup(groupName,false,false));
		finalName += intToStrTemp;
		finalName += "/";
		intToStrTemp.Format("%d",getBuddyCount());
		finalName += intToStrTemp;
		finalName += ")";
		
	}

	SetItemText(groupItem,finalName);
}

void MiaBuddyList::refreshBuddyData(CString thisBuddyName,int newStatus,
	int newEvil,int newsignonTime,int newidleTime,int newbuddyClass)
{
	//get the buddy item
	HTREEITEM buddyItem = getBuddyItem(thisBuddyName);
	
	if (buddyItem == 0)
	{
		//AfxMessageBox("could not update buddy data for buddy:" + thisBuddyName);
		return;
	}
	

	//get the last on time for the buddy
	//compute the string version of the idle time
	CString newlastOnString;
	if (newStatus != BUDDY_STATUS_OFFLINE)
	{
		newlastOnString = "Now";
	}
	else  
	{
		CTime time;
		time = CTime::GetCurrentTime();
		newlastOnString = time.Format("%d/%m/%Y %H:%M:%S");
	}


	//set the idle time of the buddy
	//compute the string version of the idle time
	//if the buddy is not online then he has no idle time
	if (newStatus == BUDDY_STATUS_OFFLINE)
	{
		//this will only happen if a person is idle and they sign offline
		newidleTime = 0;
		//however it should not be nessesary if what is comming into this function
		//is right
	}
	
	CString newidleTimeString;;
	int minute = newidleTime;
	int hour = 0;
	//take and get the hours if necessary
	while (minute > 59)
	{
		hour++;				//new hour
		minute = minute-60;	//less 60 sminutes
	}
	
	//if there is no idle time
	if (hour == 0 && minute == 0)
		newidleTimeString = "Active";
	else	//format the idle time
		newidleTimeString.Format("%d%s%d%s",hour,"h ",minute,"m");

	//get the pointer
	DWORD temp = GetItemData(buddyItem);

	//cast to buddy pointer
	MiaBuddy* thisBuddy = (MiaBuddy*)temp;
	
	thisBuddy->userClass = newbuddyClass;
	thisBuddy->signonTime = newsignonTime;
	thisBuddy->idleTime = newidleTime;
	thisBuddy->evil = newEvil;
	thisBuddy->lastOnString = newlastOnString;
	thisBuddy->idleTimeString = newidleTimeString;
	

	//set the buddy status so it can change how the buddy looks if necessary
	setBuddyStatus(thisBuddyName, newStatus);
	
}

HTREEITEM MiaBuddyList::moveItem( HTREEITEM hItem, HTREEITEM htiNewParent, 
                                       HTREEITEM htiAfter /*= TVI_LAST*/ )
{
    TV_INSERTSTRUCT tvstruct;
	HTREEITEM hNewItem;
    CString sText;

    // get information of the source item
    tvstruct.item.hItem = hItem;
    tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE |     TVIF_IMAGE | TVIF_SELECTEDIMAGE;
    GetItem(&tvstruct.item);  
    sText = GetItemText( hItem );
        
    tvstruct.item.cchTextMax = sText.GetLength();
    tvstruct.item.pszText = sText.LockBuffer();

    //insert the item at proper location
    tvstruct.hParent = htiNewParent;
    tvstruct.hInsertAfter = htiAfter;
    tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    hNewItem = InsertItem(&tvstruct);
    sText.ReleaseBuffer();

    //now copy item data and item state.
    SetItemData(hNewItem,GetItemData(hItem));
    SetItemState(hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	//now delete the old item
	DeleteItem(hItem);

    return hNewItem;
}




HTREEITEM MiaBuddyList::addBuddy(CString name, CString groupName, bool isOnline)
{
	groupName = normalizeGroupName(groupName);
	HTREEITEM buddyWasAdded;

	//check if the buddy already exists
	if (getBuddyItem(name) == 0)
	{
		MiaBuddy* newBuddy = new MiaBuddy;
		
		newBuddy->groupName = groupName;
	

		HTREEITEM theGroup = getGroupItem(groupName);
		//if the group actually exists add the buddy to it
		if (theGroup != 0)
		{
			buddyWasAdded = InsertItem(name, ICON_BUDDY_DEFAULT, ICON_BUDDY_DEFAULT,theGroup,TVI_SORT);
			//buddyWasAdded = InsertItem(TVIF_SELECTEDIMAGE | TVIF_IMAGE | TVIF_TEXT | TVIF_HANDLE,name,ICON_BUDDY_DEFAULT,
			//	ICON_BUDDY_DEFAULT,0,0,0,theGroup,theGroup);
			SetItemData(buddyWasAdded,(DWORD)newBuddy);
		}
		//create the group then add the buddy
		else	
		{
			theGroup = addGroup(groupName);
			buddyWasAdded = InsertItem(name, ICON_BUDDY_DEFAULT, ICON_BUDDY_DEFAULT,theGroup,TVI_SORT);
			//	buddyWasAdded = InsertItem(TVIF_SELECTEDIMAGE | TVIF_IMAGE | TVIF_TEXT | TVIF_HANDLE,name,ICON_BUDDY_DEFAULT,
			//	ICON_BUDDY_DEFAULT,0,0,0,theGroup,theGroup);
			SetItemData(buddyWasAdded,(DWORD)newBuddy);
		}
		if (buddyWasAdded == 0)
			AfxMessageBox("could not add item");
		
		moveBuddyOffline(name);

		//this just expands the group the buddy was added to
		HTREEITEM hParent = GetParentItem(buddyWasAdded);
		if (hParent != NULL)
			Expand(hParent, TVE_EXPAND);

	}
	
	return buddyWasAdded;
}

//must deallocate item buddy object
void MiaBuddyList::OnDestroy() 
{
	CTreeCtrl::OnDestroy();
}

void MiaBuddyList::delBuddy(CString buddyName)
{
	HTREEITEM buddyItem = getBuddyItem(buddyName);
	if (buddyItem != 0)
	{
		DeleteItem(buddyItem);
	}
}


CString MiaBuddyList::getBuddyAlias(int num) const
{
	CString temp;
	return temp;
}

int MiaBuddyList::getBuddyGroup(int num) const
{
	return 0;
}

int MiaBuddyList::getBuddyStatus(CString buddyName)
{
	HTREEITEM buddyItem = getBuddyItem(buddyName);
	DWORD temp = GetItemData(buddyItem);
	MiaBuddy* thisBuddy = (MiaBuddy*)temp;
	
	return thisBuddy->status;
}

void MiaBuddyList::setBuddyStatus(CString buddyName, int status)
{
	HTREEITEM buddyItem = getBuddyItem(buddyName);
	//this will happen if server sends an update for a buddy
	//that is not on my list
	if (buddyItem == 0)
	{
		//AfxMessageBox("could not set status of:" + buddyName);
		return;
	}
		
	DWORD temp = GetItemData(buddyItem);
	MiaBuddy* thisBuddy = (MiaBuddy*)temp;
	CString groupName = thisBuddy->groupName;

	int oldStatus = thisBuddy->status;
	thisBuddy->status = status;
	

	
	TVITEM item;
	item.hItem = buddyItem;
	item.mask = TVIF_SELECTEDIMAGE | TVIF_IMAGE;	

	GetItem(&item);
		
	if (status == BUDDY_STATUS_AWAY)
	{
		item.iImage = ICON_BUDDY_AWAY;
		item.iSelectedImage = ICON_BUDDY_AWAY;
		SetItem(&item);
		if (oldStatus == BUDDY_STATUS_ONLINE)
		{
			TRACE("buddy away so calling proccesssystemmessage for user " + buddyName + "\r\n");
			MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(GetParentFrame());
			CString smessage = "Buddy Is Away";
			theMainParent->processSystemMessage(buddyName,smessage,false);
		}
		if (oldStatus == BUDDY_STATUS_OFFLINE)
		{
			MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(GetParentFrame());
			CString smessage = "Buddy Signed On";
			theMainParent->processSystemMessage(buddyName,smessage,false);
			moveBuddyOnline(buddyName);
		}
	}
	/*
	else if (status == BUDDY_STATUS_IDLE)
	{
		item.iImage = ICON_BUDDY_IDLE;
		item.iSelectedImage = ICON_BUDDY_IDLE;
		SetItem(&item);
		if (oldStatus == BUDDY_STATUS_OFFLINE)
			moveBuddyOnline(buddyName);
	}
	*/
	else if (status == BUDDY_STATUS_ONLINE)
	{
		if (thisBuddy->userClass == BUDDY_TYPE_AOL)
		{
			item.iImage = ICON_BUDDY_AOL;
			item.iSelectedImage = ICON_BUDDY_AOL;
		}
		else if (thisBuddy->userClass == BUDDY_TYPE_UNCONFIRMED)
		{
			item.iImage = ICON_BUDDY_AIM;
			item.iSelectedImage = ICON_BUDDY_AIM;
		}
		else if (thisBuddy->userClass == BUDDY_TYPE_NORMAL)
		{
			item.iImage = ICON_BUDDY_AIM;
			item.iSelectedImage = ICON_BUDDY_AIM;
		}
		else
		{
			item.iImage = ICON_BUDDY_DEFAULT;
			item.iSelectedImage = ICON_BUDDY_DEFAULT;
		}

		
		SetItem(&item);
		if (oldStatus == BUDDY_STATUS_OFFLINE)
		{
			MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(GetParentFrame());
			CString smessage = "Buddy Signed On";
			theMainParent->processSystemMessage(buddyName,smessage,false);
			moveBuddyOnline(buddyName);
		}
		else if (oldStatus == BUDDY_STATUS_AWAY)
		{
			MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(GetParentFrame());
			CString smessage = "Buddy Came Back From Away";
			theMainParent->processSystemMessage(buddyName,smessage,false);
		}

	}
	else if (status == BUDDY_STATUS_OFFLINE)
	{
		item.iImage = ICON_BUDDY_DEFAULT;
		item.iSelectedImage = ICON_BUDDY_DEFAULT;
		SetItem(&item);
		if (oldStatus != BUDDY_STATUS_OFFLINE)
		{
			MiaMainWindow* theMainParent = reinterpret_cast<MiaMainWindow*>(GetParentFrame());
			CString smessage = "Buddy Signed Off";
			theMainParent->processSystemMessage(buddyName,smessage,false);
			moveBuddyOffline(buddyName);
		}

	}
}

///functions not implimented yet

//this starts the timer to show that a buddy has just signed on
//and then accepts the timer message to kill it
void MiaBuddyList::buddySignonDisplay(CString buddyName)
{
}

void MiaBuddyList::buddySignoffDisplay(CString buddyName)
{
}

int MiaBuddyList::setBuddyUserClass(CString buddyName, int userClass)
{
	return 0;
}

int MiaBuddyList::setBuddySignonTime(CString buddyName, int time)
{
	return 0;
}

int MiaBuddyList::setBuddyIdleTime(CString buddyName, int time)
{
	return 0;
}

int MiaBuddyList::setBuddyIdleTimeString(CString buddyName, CString time)
{
	return 0;
}

int MiaBuddyList::setBuddyEvil(CString buddyName, int evil)
{
	return 0;
}

int MiaBuddyList::setBuddyLastOn(CString buddyName, int time)
{
	return 0;
}

int MiaBuddyList::setBuddyLastOnString(CString buddyName, CString time)
{
	return 0;
}

int MiaBuddyList::setBuddyGroup(CString buddyName, int group)
{
	return 0;
}

HTREEITEM MiaBuddyList::addGroup(const CString &name)
{
	//AfxMessageBox("adding group:" + name);
	HTREEITEM addGroup = 0;
	HTREEITEM groupItem = getGroupItem(normalizeGroupName(name));
	static HTREEITEM lastAddedGroup = 0;
	
	if (groupItem == 0)
	{
		MiaBuddy* newGroup = new MiaBuddy;
		
		newGroup->isGroup = true;

		//HTREEITEM rootItem;
		//if (name == "Offline")
		//	rootItem = getGroupItem(name);
		//else
		//{
		//	rootItem = getGroupItem("Offline");
		//	rootItem = GetPrevVisibleItem(rootItem);
		//}
		//HTREEITEM rootItem = GetRootItem();

		
		//insert the group into the tree
		if (lastAddedGroup == 0)
			addGroup = InsertItem(name, ICON_GROUP_DEFAULT_COLLAPSED, ICON_GROUP_DEFAULT,0,TVI_FIRST);
		else
			addGroup = InsertItem(name, ICON_GROUP_DEFAULT_COLLAPSED, ICON_GROUP_DEFAULT,0,lastAddedGroup/*TVI_SORT TVI_LAST*/);
			

		SetItemData(addGroup,(DWORD)newGroup);
		//expand the group by default
		if (name != "Offline")
			lastAddedGroup = addGroup;
		else
			lastAddedGroup = 0;

		Expand(addGroup,TVE_EXPAND);
	}

	return addGroup;
}

void MiaBuddyList::delGroup(CString groupName)
{

	HTREEITEM groupItem = getGroupItem(groupName);
	if (groupItem != 0)
	{
		//delete every child of this group
		HTREEITEM currentItem = GetNextItem(groupItem,TVGN_CHILD);
		while (currentItem != NULL)
		{
			DeleteItem(currentItem);

			//get the next item for the sake of the while loop ending
			currentItem = GetNextItem(currentItem,TVGN_NEXT);
		}

		//delete the actual group now
		DeleteItem(groupItem);
	}
}

void MiaBuddyList::getListOfGroups(CList<CString,CString&>& theList)
{
	HTREEITEM groupItem = GetRootItem();
	while (groupItem != NULL)	//while there is still something in the tree
	{
		theList.AddHead(normalizeGroupName(GetItemText(groupItem)));
		groupItem = GetNextItem(groupItem,TVGN_NEXT);
	}
	
}

bool MiaBuddyList::renameGroup(const CString &oldname, const CString &newname)
{
	bool answer = false;
	HTREEITEM groupItem = getGroupItem(oldname);
	if (groupItem != 0)
	{
		SetItemText(groupItem,newname);
		answer = true;
	}
	return answer;
}

int MiaBuddyList::getGroupCount()
{
	int returnCount = 0;
	HTREEITEM groupItem = GetRootItem();
	while (groupItem != NULL)	//while there is still something in the tree
	{
		returnCount++;
		groupItem = GetNextItem(groupItem,TVGN_NEXT);
	}
	return returnCount;
}

//since i am displaying the buddy counts in the group name
//i need to be able to kill that and just have the plain group name
CString MiaBuddyList::normalizeGroupName(CString groupName)
{
	CString returnValue;
	if (groupName.Find("(") > 1)
	{
		returnValue = groupName.Left(groupName.Find("(") - 1);
	}
	else
		returnValue = groupName;

	//AfxMessageBox("norm name is:" + returnValue);

	return returnValue;
}

int MiaBuddyList::getBuddyCountInGroup(CString groupName, bool OnlineOnly, bool groupNameIsValid)
{
	//groupName = normalizeGroupName(groupName);
	int returnCount = 0;

	MiaBuddy* thisBuddy;
	
	//get the group
	HTREEITEM currentItem;
	HTREEITEM groupItem = getGroupItem(groupName);
	if (groupItem == 0)
		AfxMessageBox("tried to get group that is not in list");

	//--should check to make sure got valid group handle
	if (ItemHasChildren(groupItem) && groupNameIsValid)
	{
	//get the first buddy in the group
	currentItem = GetNextItem(groupItem,TVGN_CHILD);
	while (currentItem != NULL)	//while there is still something in the tree
	{
		//returnCount++;

		thisBuddy = reinterpret_cast<MiaBuddy*>(GetItemData(currentItem));

		//if we are paying attention to the status of a buddy
		if (OnlineOnly)
		{
			//if this buddy has that status
			if (thisBuddy->status != BUDDY_STATUS_OFFLINE)
				returnCount ++;
		}
		//there's a buddy and that's all we care about
		else
			returnCount ++;

		//get the next buddy
		currentItem = GetNextItem(currentItem,TVGN_NEXT);
	}
	}
	//now check the offline folder for anybody that needs to be counted
	groupItem = getGroupItem("Offline");
	//--should check to make sure got valid group handle

	if (ItemHasChildren(groupItem) && !OnlineOnly)
	{
	//get the first buddy in the group
	currentItem = GetNextItem(groupItem,TVGN_CHILD);
	while (currentItem != NULL)	//while there is still something in the tree
	{
		//returnCount++;

		if (groupNameIsValid)
		{
			thisBuddy = reinterpret_cast<MiaBuddy*>(GetItemData(currentItem));
			if (groupName == thisBuddy->groupName)
			{
				returnCount ++;
			}
		}
		else
			returnCount ++;


		//get the next buddy
		currentItem = GetNextItem(currentItem,TVGN_NEXT);
	}
	}


	//delete thisBuddy;

	return returnCount;
}

void MiaBuddyList::OnRButtonDown(UINT nflags,CPoint point)
//void MiaBuddyList::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	

	CPoint pos = point;
	//ScreenToClient(&pos);
	ClientToScreen(&pos);

		UINT uFlags;
		HTREEITEM hitem = HitTest(point,&uFlags); //Get item pointed by mouse
		if (hitem != NULL && (TVHT_ONITEM & uFlags))
		{

		
			
			SelectItem(hitem);
			CString text = normalizeGroupName(GetItemText(hitem));

			MiaBuddy* aBuddy = (MiaBuddy*)GetItemData(hitem);
			if (!aBuddy->isGroup)
			{
				CMenu menu;
				menu.LoadMenu(IDR_MENU_BUDDY);
				//UINT nFlags;
			
				//THIS DOESN"T FREAKING WORK FOR SOME STUPID REASON
				if (aBuddy->status == BUDDY_STATUS_OFFLINE)
				{
					//AfxMessageBox("hello");
					menu.RemoveMenu(ID_TOP_IDLETIME,MF_BYCOMMAND);
					menu.RemoveMenu(ID_TOP_WARNINGLEVEL,MF_BYCOMMAND);
					menu.RemoveMenu(ID_TOP_ONLINETIME,MF_BYCOMMAND);
					menu.RemoveMenu(ID_TOP_SERVICE,MF_BYCOMMAND);
					menu.RemoveMenu(ID_TOP_GETUSERINFO,MF_BYCOMMAND);
				}
				else
				{


				menu.ModifyMenu(ID_TOP_BUDDYNAME,MF_BYCOMMAND,0, text + " (" + aBuddy->groupName + ")");
				menu.ModifyMenu(ID_TOP_IDLETIME,MF_BYCOMMAND,0, "Idle Time: " + aBuddy->idleTimeString);
				//menu.ModifyMenu(ID_TOP_ONLINETIME,MF_BYCOMMAND,0, "Online Time: " + "who knows");
				//menu.ModifyMenu(ID_TOP_SERVICE,MF_BYCOMMAND,0, text + " (" + aBuddy->groupName + ")");
				CString warningLevel = "Warning Level: ";
				char* evilStr = new char[10];
				itoa(aBuddy->evil,evilStr,10);
				warningLevel += evilStr;
				delete [] evilStr;
				warningLevel += "%";
				menu.ModifyMenu(ID_TOP_WARNINGLEVEL,MF_BYCOMMAND,0,warningLevel);

				CString userClass = "Service: ";
				userClass += MiaBuddyList::USERCLASSSTRINGS[aBuddy->userClass];
				menu.ModifyMenu(ID_TOP_SERVICE,MF_BYCOMMAND,0,userClass);
	
				}
				

				CMenu* pContextMenu = menu.GetSubMenu (0);
				//pContextMenu->SetMenuDefaultItem(1, TRUE);


				pContextMenu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON , pos.x, pos.y, AfxGetMainWnd());
			}
		}

	CTreeCtrl::OnRButtonDown(nflags,point);
}

void MiaBuddyList::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	CTreeCtrl::OnLButtonDblClk(nFlags,point);

	//if this item doesn't have any children then it isn't a group
	//so send the message that a buddy was double clicked
	//i am going to leave it up to the main window to get the currently selected
	//item but this may not be a good idea

	HTREEITEM hitem = GetSelectedItem();
	MiaBuddy* aBuddy = (MiaBuddy*)GetItemData(hitem);

	if (!aBuddy->isGroup && aBuddy->status != BUDDY_STATUS_OFFLINE)
	{
		GetParentFrame()->SendMessage(WM_BUDDYLISTDBLCLICK);
	}

	
}
