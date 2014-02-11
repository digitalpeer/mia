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

#ifndef MIABUDDY_H
#define MIABUDDY_H

#include "stdafx.h"
class MiaBuddyList;
class MiaChatDialog;

//this is all the data for a single buddy on the buddy list
class MiaBuddy
{
	public:
	MiaBuddy();

	bool isGroup;
	int status;

	CString alias;
	
	CString groupName;

	int userClass;
	int signonTime;
	int idleTime;
	CString idleTimeString;

	//evil amount
	int evil;
	
	//int last on time in string format;
	CString lastOnString;

	int signedOn;
	
	//the chat window asociated with a particular buddy
	MiaChatDialog* myChatWindow;

	//each buddy and group has a protocol associated with it
	//so when one protocol gets disconnected or whatever, I need to
	//be able to identify the buddies in it
	int protocol;

	//this is a unique id set in the constructor for each buddy
	//this is the timer id used for signing THIS buddy on and off
	int transitionTimerID;
	
};

#endif