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


#ifndef TOCMIA_H
#define TOCMIA_H

#include "MiaBuddyList.h"

class MiaSocket;
class MiaMainWindow;

/*
these are caps that are in TOC2.0 but I don't have documentation on them

#define VOICE_UID     "09461341-4C7F-11D1-8222-444553540000"
#define FILE_SEND_UID "09461343-4C7F-11D1-8222-444553540000"
#define IMAGE_UID     "09461345-4C7F-11D1-8222-444553540000"
#define B_ICON_UID    "09461346-4C7F-11D1-8222-444553540000"
#define STOCKS_UID    "09461347-4C7F-11D1-8222-444553540000"
#define FILE_GET_UID  "09461348-4C7F-11D1-8222-444553540000"
#define GAMES_UID     "0946134a-4C7F-11D1-8222-444553540000"
*/

struct directory
{
	CString firstName;
	CString middleName;
	CString lastName;
	CString maidenName;
	CString city;
	CString state;
	CString country;
	CString email;
	bool allowWebSearches;
};


class MiaTOC 
{
	public:

		//TOC CONSTANTS
		static const CString TOC_LANG;		//define the language
		static const CString MIA_VER;		//define the client version
		static const int TOC_VER_INT;		//define the TOC version supported

		//TOC PREFERENCES
		static CString TOC_HOST;
		static CString TOC_AUTH_HOST;	//this is the auth server that is passed to the TOC_HOST seerver
		static CString TOC_AUTH_PORT;	//"5190"
		static short TOC_PORT;		//default server port to connect to


		//TOC STATUS INDICATORS
		static const int MIA_ONLINE;		//online and waiting for anything
		static const int MIA_SIGNON_STEP_0;
		static const int MIA_SIGNON_STEP_1;
		static const int MIA_SIGNON_STEP_2;
		static const int MIA_SIGNON_STEP_3;
		static const int MIA_AWAY;			//away message is on
		static const int MIA_OFFLINE;		//not connected
		static const int MIA_IDLE;			//idle

		//TOC PERMISSIONS
		static const int TOC_PERMITALL;
		static const int TOC_DENYALL;
		static const int TOC_PERMITSOME;
		static const int TOC_DENYSOME;

		//TOC USER TYPES/CLASSES
		//static const int TOC_USER_AOL;
		//static const int TOC_USER_ADMIN;
		//static const int TOC_USER_UNCONFIRMED;
		//static const int TOC_USER_NORMAL;
		//static const int TOC_USER_AWAY;
		//static const CString USERCLASSSTRINGS[5];


		//SFLAP FRAME TYPES
		static const int SFLAP_TYPE_SIGNON;
		static const int SFLAP_TYPE_DATA;
		static const int SFLAP_TYPE_ERROR;
		static const int SFLAP_TYPE_SIGNOFF;
		static const int SFLAP_TYPE_KEEPALIVE;

		//OTHER CONSTANTS
		static const int SFLAP_HEADERSIZE;


		MiaTOC(MiaMainWindow* parent = 0, MiaBuddyList* theList = 0);
		~MiaTOC();
		
		MiaBuddyList* buddyList;
		
		void InitConfig(CString data);

		void setPermitList(const MiaBuddyList &);
		void setDenyList(const MiaBuddyList &);
		void setPermissions(int);
        void tocremoveBuddy(const MiaBuddyList &, const CString &);
        void tocaddBuddy(const MiaBuddyList &, const CString &);

		int getStatus();
		inline CString getUserName(void) { return username; };

		void doIdleTime(bool);

		void setServerBuddyList(const MiaBuddyList &);
		void setServerPermitList(const MiaBuddyList &);
		void setServerDenyList(const MiaBuddyList &);
		void setServerPermissions(int);
		
		void setMiaStatus(int theStatus);

		//how I did this is rather odd...when TOC connects, it converts the config
		//password to the roasted password and saves it locally and also copies the
		//config username locally
		//this just makes sure that once signed on, the username is set
		void setCredentialsAndConstants();
		
		CString currentAwayMessage;
		void setAwayMessage(const CString &message);
		void setAwayMessageOff();

		void setUserInfo(const CString &);

		void requestUserInfo(CString name);

		void sendIM(CString, CString, bool, bool);

		void sendWarning(CString, bool);

		void changePassword(CString oldPassword, CString newPassword);

		void requestDirectory(const CString &);

		void setDirectory(const directory &);

		void searchDirectory(const directory &);

		void debugDataIn(CString data);
		void statusChanged(int);	
		void configChanged(void);
		void buddyChanged(int);
		void idleTimeReached();

		void nick(CString name);

		void userSignedOn(CString);
		void userNotIdle(CString);
		void userNotAway(CString);
		    
		void userNameChanged(void);
		void userInfoReceived(CString);

		void IMReceived(CString, CString, bool);
		void warningReceived(int, CString);
		void warningReduced(int, CString);
	
		// error messages (from server, and local)
		void displayError(CString);

		// sign-on process
		void tocConnect(void);
		void tocConnect1(void);
		
		void tocConnect2(CString &data);
		void tocConnect3(void);
		void onDisconnect(void);
		void doDisconnect();

		// parsing commands from the server given by the socket
		void tocServer(CString &data);

		// idleTime
		void endIdleness(void);
		void updateIdleness(void);


		int status;
		MiaMainWindow* myParentWindow;
		MiaSocket* theSocket;

		int keepAlive;

		CString server;
		int serverPort;
		CString authorizer;
		int authorizerPort;

		// so we don't send the buddy list n times
		CString lastListSent;
		int lastPermissionSent;
		CString lastInfoSent;
		CString lastConfigSent;

		// secondary thread host lookup stuff
		int hostThreadReturn;

		// user information and configuration
		CString username;
		CString r_password;
		CString userInfo;

		// save old warning level, so we can tell the difference between warnings and reductions
		int oldEvil;

		void OnReceiveUserInfo(CString data);

		// idleness
		bool updateIdleTime;
		time_t idleTime;
		bool isIdle;

		
		void tocSignon(const CString &auth_host, const CString &auth_port, const CString &lang);
		void tocInitDone(void);
		void setConfig(void);
		void sendConfig(void);
		void sendPermissions(void);
		void sendUserInfo(void);
		void doNick(const CString &);
		void doUpdateBuddy(const CString &);
		void doIM(const CString &);
		void doEviled(const CString &);
		void doError(CString &data, bool killConnection = false);
		
		void doPasswordMessage(const CString &);


		//all sorts of chat functions
		void chatSend(int room, CString message);
		void chatWhisper(int room, CString dst_bud, CString message);
		void chatInvite(int room, CString message, CString buddy);
		void chatLeave(int room);
		void chatAccept(int room);

		void chatJoin(CString name, int Exchange);

		void doChatJoin(const CString &);
		void doChatIn(const CString &);
		void doChatUpdateBuddy(const CString &);
		void doChatInvite(const CString &);
		void doChatLeft(const CString &);


		bool SaveListToFile(bool askForPath);
		bool LoadListFromFile(bool askForPath);
};

#endif

