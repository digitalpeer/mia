

//define custom messages for window communication
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


#define WM_SENDMESSAGE (WM_USER + 100)
#define WM_RECEIVEMESSAGE (WM_USER + 101)
#define WM_NEWDEBUGMESSAGE (WM_USER + 102)
#define WM_BUDDYLISTDBLCLICK (WM_USER + 103)
//#define WM_DOSIGNON (WM_USER + 104)
//#define WM_SIGNONDLGRECEIVESTATUS (WM_USER + 105)
//#define WM_ONSIGNONDLGDESTROYED (WM_USER + 106)
#define WM_ONEDITINFODLGDESTROYED (WM_USER + 107)
#define	WM_ICON_NOTIFY			WM_APP+10

//disable those dang annoying warnings so I don't
//have to wade through them
#pragma warning( disable : 4244)	//double to int
#pragma warning( disable : 4700)

