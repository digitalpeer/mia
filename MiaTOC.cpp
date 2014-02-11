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
#include "StdAfx.h"
#include "Mia.h"
#include "MiaSocket.h"
#include "MiaBuddyList.h"
#include "MiaMainWindow.h"
#include "MiaTOC.h"
#include "MiaInfoDlg.h"
#include "MiaConfig.h"

#include "MiaFileFunc.h"

//TOC CONSTANTS
const CString MiaTOC::TOC_LANG =		"english";
//const CString MiaTOC::MIA_VER =			"MIA001";
//const int MiaTOC::TOC_VER_INT =			1;

const CString MiaTOC::MIA_VER =			"MIA:$Revision: 0.0.1$";
const int MiaTOC::TOC_VER_INT =			98262528;



//TOC PREFERENCES
CString MiaTOC::TOC_HOST =		"toc.oscar.aol.com";
short MiaTOC::TOC_PORT =		5190; //5190 //9898
CString MiaTOC::TOC_AUTH_HOST =	"login.oscar.aol.com";
CString MiaTOC::TOC_AUTH_PORT =	"5190";



//TOC STATUS INDICATORS
const int MiaTOC::MIA_ONLINE =			1;
const int MiaTOC::MIA_SIGNON_STEP_0 =	2;
const int MiaTOC::MIA_SIGNON_STEP_1 =	3;
const int MiaTOC::MIA_SIGNON_STEP_2 =	4;
const int MiaTOC::MIA_SIGNON_STEP_3 =	5;
const int MiaTOC::MIA_AWAY =			6;
const int MiaTOC::MIA_OFFLINE =			0;
const int MiaTOC::MIA_IDLE =			7;

//TOC PERMISSIONS
const int MiaTOC::TOC_PERMITALL =	1;
const int MiaTOC::TOC_DENYALL =		2;
const int MiaTOC::TOC_PERMITSOME =	3;
const int MiaTOC::TOC_DENYSOME =	4;


//TOC USER TYPES/CLASSES
//const int MiaTOC::TOC_USER_AOL =			1;
//const int MiaTOC::TOC_USER_ADMIN =			2;
//const int MiaTOC::TOC_USER_UNCONFIRMED =	3;
//const int MiaTOC::TOC_USER_NORMAL =			4;
//const int MiaTOC::TOC_USER_AWAY =			5;

//SFLAP FRAME TYPES
const int MiaTOC::SFLAP_TYPE_SIGNON =		1;
const int MiaTOC::SFLAP_TYPE_DATA = 		2;
const int MiaTOC::SFLAP_TYPE_ERROR = 		3;
const int MiaTOC::SFLAP_TYPE_SIGNOFF =		4;
const int MiaTOC::SFLAP_TYPE_KEEPALIVE =	5;

//OTHER CONSTANTS
const int MiaTOC::SFLAP_HEADERSIZE =	6;

void MiaTOC::OnReceiveUserInfo(CString data)
{
	//delete the "GOTO_URL" and for now delete the ":TIC:"
	data.Delete(0,13);
	//save the user info to a local file



	//if there is a window open asking for the info, give it to it
	if (myParentWindow->m_infoDlg != 0)
		myParentWindow->m_infoDlg->OpenUserInfoFile(data);
}


MiaTOC::MiaTOC(MiaMainWindow *parent,MiaBuddyList* theList):myParentWindow(parent),buddyList(theList)
{
	//set the status offline
	setMiaStatus(MIA_OFFLINE);
	
	//set socket 0
	theSocket = 0;

	//set username to nothing
	username.Empty();

	//set roasted password to nothing
	r_password.Empty();

	//set user info nothing
	userInfo.Empty();
	
	idleTime = 0;
	isIdle = false;
}

MiaTOC::~MiaTOC()
{
	setMiaStatus(MIA_OFFLINE);
}


//this will save whetever is in the tree to a file
bool MiaTOC::SaveListToFile(bool askForPath)
{

	TCHAR fileFilters[] = _T("Text files (*.txt)|*.txt|All files (*.*|*.*||");
	CFileDialog fileSaveDlg (TRUE,_T("txt"),_T("*.txt"),
		0,fileFilters);

	if (fileSaveDlg.DoModal() == IDOK)
	{

	CStdioFile saveFile(fileSaveDlg.GetPathName(), CFile::modeWrite | CFile::modeCreate);
		
	//groupItem = 
	HTREEITEM groupItem = buddyList->GetRootItem();
	HTREEITEM currentItem;
	
	bool firstPass = true;
	saveFile.WriteString("g " + buddyList->GetItemText(groupItem) + "\n");

	while (groupItem != 0)	//while there is still something in the tree
	{
		
		currentItem = buddyList->GetNextItem(groupItem,TVGN_CHILD);
		saveFile.WriteString("g " + buddyList->GetItemText(groupItem) + "\n");
		

		while (currentItem != 0)	//while there is still something in the tree
		{
			saveFile.WriteString("b " + buddyList->GetItemText(currentItem) + "\n");
			currentItem = buddyList->GetNextItem(currentItem,TVGN_NEXT);
		}

		saveFile.WriteString("g " + buddyList->GetItemText(groupItem) + "\n");
		groupItem = buddyList->GetNextItem(groupItem,TVGN_NEXT);
		
		
		
	}

	//close the file (don't have to but just makes me feel better)
	saveFile.Close();

	}

	return true;
}

bool MiaTOC::LoadListFromFile(bool askForPath)
{

	CString buddyListData;
	CString buffer;
	CString fileName;
	
	
	if (askForPath)
	{
	TCHAR fileFilters[] = _T("Text files (*.txt)|*.txt|All files (*.*|*.*||");
	CFileDialog fileLoadDlg (TRUE,_T("txt"),_T("*.txt"),
		OFN_FILEMUSTEXIST,fileFilters);

		if (fileLoadDlg.DoModal() == IDOK)
			fileName = fileLoadDlg.GetPathName();
	}
	else
		fileName = "list.txt";


	if (!fileName.IsEmpty())
	{

	
	CStdioFile loadFile(fileName, CFile::modeRead);

	while(loadFile.ReadString(buffer))
		buddyListData += buffer + "\n";
		

	loadFile.Close();

	InitConfig("CONFIG:" + buddyListData);
	
	}
	
	return true;

}

//this takes a clean buddy list and fills it up with a CONFIG from TOC
void MiaTOC::InitConfig(CString data)
{
	/*
	config format:

	CONFIG:g group1
	b Buddy1
	b Digitalpeer
	b Buddy2
	b Buddy3
	g group2
	b Buddy4
	*/

	int i;
	CString thisData;
	CString thisDataType;
	MiaBuddy newBuddy;
	CString currentGroupName;

	buddyList->DeleteAllItems();
	buddyList->addGroup("Offline");

	//get rid of CONFIG:
	data.Delete(0,7);
	
	//slowly chop away at the string of data putting stuff where it goes
	while(data.GetLength() > 0)
	{
		//first delete 2 endline characters
		//data.Delete(0, 2);
		thisDataType = data.GetAt(0);
		data.Delete(0, 2);	

		//find the end of this line now
		i = data.Find("\n");
        if(i != -1)						//get up to the next end line
        {
			thisData = data.Left(i);	//save this data
            data.Delete(0, i + 1);		//delete what was taken out
        }
        else							//else get the rest of the data
        {
			thisData = data;			//save this data
            data.Delete(0, data.GetLength());	//delete the rest
		}
		
		//myParentWindow->UpdateDebug("Current data is: " + thisData);

		if (thisDataType == "m")
		{
			//*permitStatus = holding.toInt();
			myParentWindow->UpdateDebug("CAN NOT HANDLE M YET");
		}
		else if (thisDataType == "g")
		{
			// now add the name to the config, saving the current group number
			 buddyList->addGroup(thisData);
			 myParentWindow->UpdateDebug("Add Group: " + thisData);
			 currentGroupName = thisData;
			//if (group == -1)
			//	group = buddyList->getGroupNum(holding);
		}
		else if (thisDataType == "b")
		{			
			myParentWindow->UpdateDebug("Add Buddy: " + thisData);
			buddyList->addBuddy(tocNormalize(thisData),currentGroupName);
		}
		else if (thisDataType == "p")
		{
			//permitList->add(&buddy);
			myParentWindow->UpdateDebug("CAN NOT HANDLE P YET");
				
		}
		else if (thisDataType == "d")
		{
			myParentWindow->UpdateDebug("CAN NOT HANDLE D YET");
			//denyList->add(&buddy);
		}
		//else
		//{
		//	AfxMessageBox("got a type and I don't know what to do with it");
		//}
	}

	
	

	
}

int MiaTOC::getStatus()
{
	return status;
}

void MiaTOC::tocConnect(void)
{
	// don't bother if already connected
	if(status != MIA_OFFLINE)
	{
		AfxMessageBox("Already connected and trying to connect again");
		return;
	}

	if (theSocket)
	{
		theSocket->Close();
		delete theSocket;
	}

	setMiaStatus(MIA_SIGNON_STEP_0);
	
	//setPassword("pass");
	//setUserName("username");

	 setCredentialsAndConstants();
	
	//LoadListFromFile(false);

	if(username.IsEmpty())
	{
		AfxMessageBox("No username specified.");
		setMiaStatus(MIA_OFFLINE);
		return;
	}
		
		if(r_password.IsEmpty())
		{
			AfxMessageBox("No password specified.");
			setMiaStatus(MIA_OFFLINE);
			return;
		}
			
		myParentWindow->UpdateStat(_T("Initializing connection to server..."));
		myParentWindow->UpdateDebug(_T("Initializing connection to server..."));
		
		theSocket = new MiaSocket(this);

		if (!theSocket->Create(0,SOCK_STREAM))
		{
			delete theSocket;
			theSocket = 0;
			AfxMessageBox("Error Creating Socket");
			setMiaStatus(MIA_OFFLINE);
			return;
		}

		while (!theSocket->Connect(TOC_HOST, TOC_PORT))
		{
			if (AfxMessageBox("Try to connect to another server?",MB_YESNO) == IDNO)
			{
				delete theSocket;
				theSocket = 0;
				setMiaStatus(MIA_OFFLINE);
				return;
			}
		}

		myParentWindow->UpdateDebug(_T("Connection made!"));
		myParentWindow->UpdateStat(_T("Connection made!"));

			
		myParentWindow->UpdateDebug(_T("Waiting for reply..."));
		myParentWindow->UpdateStat(_T("Connection made!"));
		
		int bytes = theSocket->Send("FLAPON\r\n\r\n", 10);
		//myParentWindow->UpdateDebug(_T("String Flap Sent"));

		if (bytes != 10)
			AfxMessageBox("oh no");
			
}

void MiaTOC::tocConnect1()
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		setMiaStatus(MIA_OFFLINE);
		return;
	}

	setMiaStatus(MIA_SIGNON_STEP_1);
	
	myParentWindow->UpdateDebug(_T("Sending signon..."));
	myParentWindow->UpdateStat(_T("Sending signon..."));

	theSocket->writeSignon( 1, 1, username);

	tocSignon(TOC_AUTH_HOST, TOC_AUTH_PORT, TOC_LANG);
		
	myParentWindow->UpdateDebug(_T("Waiting for authorization..."));
	myParentWindow->UpdateStat(_T("Waiting for authorization..."));

}


void MiaTOC::tocConnect2(CString &data)
{
	

	//AfxMessageBox("into 2!");
	if(!theSocket)
	{
		setMiaStatus(MIA_OFFLINE);
		myParentWindow->UpdateDebug(_T("Unknown Error!"),true,true);
		return;
	}

	setMiaStatus(MIA_SIGNON_STEP_2);
	

	if(data.Left(6) == "ERROR:")
	{
		doError(data);
		setMiaStatus(MIA_OFFLINE);
		myParentWindow->UpdateDebug(_T("Unknown Error!"),true,true);
		return;
	}
	else if(data.Left(8) != "SIGN_ON:")
	{
		myParentWindow->UpdateDebug(_T("RESPONSE TO signon is not TOC SIGN_ON"),true,true);
		myParentWindow->UpdateDebug(_T("RESPONSE was:" + data),true,true);
		setMiaStatus(MIA_OFFLINE);
		return;
	}
		
	myParentWindow->UpdateDebug(_T("Checking for configuration..."));
	myParentWindow->UpdateStat(_T("Checking for configuration..."));

	tocConnect3();
}


void MiaTOC::tocConnect3()
{
	if(!theSocket)
	{
		myParentWindow->UpdateDebug(_T("Unknown Error!"),true,true);
		setMiaStatus(MIA_OFFLINE);
		return;
	}
	
	setMiaStatus(MIA_SIGNON_STEP_3);

	myParentWindow->UpdateDebug(_T("Sending configuration..."));
	myParentWindow->UpdateStat(_T("Sending configuration..."));

	myParentWindow->UpdateDebug(_T("Completing signon..."));
	myParentWindow->UpdateStat(_T("Completing signon..."));

	tocInitDone();

	setMiaStatus(MIA_ONLINE);
	myParentWindow->UpdateStat(_T("MIA is now Online."));

	setUserInfo(MiaLoadFile(MiaConfig::LOCAL_INFO_FILE_PATH));
}


void MiaTOC::tocSignon(const CString &auth_host, const CString &auth_port, const CString &lang)
{
	
	CString data;

	data.Format("toc_signon %s %s %s %s %s %s",
		auth_host,
		auth_port,
		username = tocNormalize(username),
		r_password,
		TOC_LANG,
		tocProcess(MIA_VER));

	// frame is set up, now send it
    theSocket->writeData(data,SFLAP_TYPE_DATA);
	
}


void MiaTOC::setPermitList(const MiaBuddyList &a)
{
	//currentConfig.permitList = a;
	sendPermissions();
}

void MiaTOC::setDenyList(const MiaBuddyList &a)
{
	//currentConfig.denyList = a;
	sendPermissions();
}

void MiaTOC::setPermissions(int a)
{
	//currentConfig.permitStatus = ( 1 <= a && 4 >= a ) ? a : 1;
	sendPermissions();
}

void MiaTOC::doIdleTime(bool doit)
{
	updateIdleTime = doit;
}



void MiaTOC::setServerBuddyList(const MiaBuddyList &a)
{
	setConfig();
}

void MiaTOC::setServerPermitList(const MiaBuddyList &a)
{
	setConfig();
}

void MiaTOC::setServerDenyList(const MiaBuddyList &a)
{
	setConfig();
}

void MiaTOC::setServerPermissions(int a)
{
	//serverConfig.permitStatus = a;
	setConfig();
}

/*
void MiaTOC::setMiaStatus(int newstatus)
{
	// this guards against a double delete
	if(newstatus == status)
		return;
	status = newstatus;
	if(theSocket)
	{
		delete theSocket;
		theSocket = 0;
	}
	if(status == TAIM_ONLINE)
		tocConnect();
	///	emit statusChanged(status);
}
*/

//set the plain text password and roast it at the same time
void MiaTOC:: setCredentialsAndConstants()
{
	r_password = tocRoast(myParentWindow->config.m_tocPassword);
	username = myParentWindow->config.m_tocUsername;
}

void MiaTOC::setUserInfo(const CString &a)
{
	userInfo = a;
	MiaSaveFile(MiaConfig::LOCAL_INFO_FILE_PATH,userInfo);
	sendUserInfo();
}

void MiaTOC::requestUserInfo(CString name)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	CString data;
	CString tempName = tocNormalize(name);
	//format the request
	data.Format("toc_get_info %s",tempName);
	//send the data
	theSocket->writeData(data,SFLAP_TYPE_DATA);

}

void MiaTOC::sendIM(CString message, CString target, bool isAuto, bool endIdleNess)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}


	CString outMessage = message;
	if(isAuto)
	{
		CString currentTime = CTime::GetCurrentTime().Format("%x");
		CString currentDate = CTime::GetCurrentTime().Format("%X");

		outMessage.Replace("%d", currentDate);
		outMessage.Replace("%t", currentTime);
		outMessage.Replace("%n", target);
	}
	
	CString data;
	CString buddyToSendTo = tocNormalize(target);
	CString buddyMessage = tocProcess(outMessage);
	data.Format("toc_send_im %s %s",buddyToSendTo,buddyMessage);
	//AfxMessageBox(data);
	if(isAuto)
	{
		CString currentTime = CTime::GetCurrentTime().Format("%x");
		CString currentDate = CTime::GetCurrentTime().Format("%X");

		outMessage.Replace("%d", currentDate );
		outMessage.Replace("%t", currentTime );
		outMessage.Replace("%n", target );

		data += " auto";
	}
	
	//printf("string: %s\n", data.data());
	theSocket->writeData(data,SFLAP_TYPE_DATA);//writeData
	//if (isAuto == false && endIdleNess == true)
	//	endIdleness();
}

void MiaTOC::sendWarning(CString target, bool isAnonymous)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	CString data;
	//format the output
	data.Format("toc_evil %s %s", tocNormalize(target), isAnonymous ? "anon" : "norm");
	//send it
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}

void MiaTOC::changePassword(CString oldPassword, CString newPassword)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}
	
	CString data;
	data.Format("toc_change_passwd %s %s", tocNormalize(oldPassword),tocNormalize(newPassword) );
	theSocket->writeData(data,SFLAP_TYPE_DATA);
	endIdleness();
}


void MiaTOC::setAwayMessageOff()
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	currentAwayMessage="";
	myParentWindow->UpdateStat(_T("MIA is Online"));

	setMiaStatus(MIA_ONLINE);
	theSocket->writeData("toc_set_away",SFLAP_TYPE_DATA);
}

void MiaTOC::setAwayMessage(const CString &message)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}
	
	setMiaStatus(MIA_AWAY);
	myParentWindow->UpdateStat(_T("MIA is Away"));

	CString awaymessage = message;
	if (awaymessage.GetLength() > 1000)
	{
		awaymessage = awaymessage.Mid(0, 950);
		awaymessage = awaymessage + "... Im me for the rest of this away message.";
	}

	currentAwayMessage = message;
	
	CString data;
	data.Format("toc_set_away %s", tocProcess(awaymessage));
	theSocket->writeData(data,SFLAP_TYPE_DATA);

	//if(message.IsEmpty() || message.GetLength() == 0)
	//	endIdleness();
}




void MiaTOC::onDisconnect(void)
{
	doDisconnect();
	myParentWindow->UpdateStat(_T("Offline"));
	myParentWindow->UpdateDebug(_T("Disconnected."));
	
}

void MiaTOC::doDisconnect()
{
	setMiaStatus(MIA_OFFLINE);
	if (theSocket != 0)
		theSocket->Close();
}


//process/parse a server to client data
void MiaTOC::tocServer(CString &data)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	//CString data = theSocket->readInBuffer();

	myParentWindow->UpdateDebug(_T("Received:") + data);


	// do what needs to be done with each incomming data
	
	//sign on message called in response to sign on
	if (status == MIA_SIGNON_STEP_0)
	{
		//myParentWindow->UpdateDebug(_T("calling tocconect1"));
		tocConnect1();
	}
	else if (status == MIA_SIGNON_STEP_1)
	{
		//myParentWindow->UpdateDebug(_T("calling tocconect2"));
		tocConnect2(data);
	}
	else
	{
		//else if (status == MIA_SIGNON_STEP_2)
		//{
		//	myParentWindow->UpdateDebug(_T("calling tocconect3"));
		//	tocConnect3();
		//}
		//else if (status == MIA_SIGNON_STEP_3)
		//{
		//	AfxMessageBox("I don't know what to do, never gotten this far");
		//}
		if (data.Left(7) == "SIGN_ON")
		{
			myParentWindow->UpdateDebug(_T("Received TOC SIGN_ON (must be comming back from pause)"));
		}
	
	//config message asking for your lists
	else if (data.Left(6) == "CONFIG")
	{
		
		myParentWindow->UpdateDebug(_T("Received TOC CONFIG"));

		InitConfig(data);

				CString configData;
	
	HTREEITEM groupItem = buddyList->GetRootItem();
	while (groupItem != 0)	//while there is still something in the tree
	{
		HTREEITEM currentItem = buddyList->GetNextItem(groupItem,TVGN_CHILD);
		while (currentItem != 0)	//while there is still something in the tree
		{
			configData = configData + buddyList->GetItemText(currentItem) + " ";
			currentItem = buddyList->GetNextItem(currentItem,TVGN_NEXT);
		}
		groupItem = buddyList->GetNextItem(groupItem,TVGN_NEXT);
	}
	
	theSocket->writeData("toc_add_buddy " + configData,SFLAP_TYPE_DATA);

		theSocket->writeData("toc_add_permit",SFLAP_TYPE_DATA);
		theSocket->writeData("toc_add_deny",SFLAP_TYPE_DATA);

				
	}
	
	else if (data.Left(4) == "NICK")
	{
		myParentWindow->UpdateDebug(_T("Received TOC NICK"));
		
				
	}

	//an incomming IM
	else if (data.Left(5) == "IM_IN")
	{
		myParentWindow->UpdateDebug(_T("Received TOC IM_IN"));
		doIM(data);
	}

	//update a buddy to a different status
	else if (data.Left(12) == "UPDATE_BUDDY")
	{
		myParentWindow->UpdateDebug(_T("Received TOC UPDATE_BUDDY"));
		doUpdateBuddy(data);

	}

	//an error has occured
	else if (data.Left(5) == "ERROR")
	{
		myParentWindow->UpdateDebug(_T("Received TOC ERROR"));
	}

	//who knows
	else if (data.Left(19) == "ADMIN_PASSWD_STATUS")
	{
		myParentWindow->UpdateDebug(_T("Received TOC ADMIN_PASSWD_STATUS"));
	}

	//somebody warned you
	else if (data.Left(6) == "EVILED")
	{
		myParentWindow->UpdateDebug(_T("Received TOC EVILED"));
		
	}

	
	//else if (data.Left(9) == "CHAT_JOIN")
	//{
	//}

	//asked to join a chat
	//else if (data.Left(11) == "CHAT_INVITE")
	//{
	//}
	
	//else if (data.Left(7) == "CHAT_IN")
	//{
	//}
	//else if (data.Left(17) == "CHAT_UPDATE_BUDDY")
	//{
	//}
	//else if (data.Left(9) == "CHAT_LEFT")
	//{
	//}
	else if (data.Left(8) == "GOTO_URL")
	{
		myParentWindow->UpdateDebug(_T("Received TOC GOTO_URL"));
		OnReceiveUserInfo(data);
	}

	//over the rate limit, any outgoing commands are paused until SIGN_ON received
	else if (data.Left(5) == "PAUSE")
	{
		myParentWindow->UpdateDebug(_T("Received TOC PAUSE"));
	}

	//no clue
	else if (data.Left(13) == "RVOUS_PROPOSE")
	{
		myParentWindow->UpdateDebug(_T("Received TOC RVOUS_PROPOSE"));
	}
	else
		myParentWindow->UpdateDebug(_T("RECIEVED UNKNOWN TOC COMMAND"));
	
	}
	
}

void MiaTOC::endIdleness(void)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	idleTime = time(0);
	if(isIdle)
	{
		isIdle = false;
		theSocket->writeData("toc_set_idle 0",SFLAP_TYPE_DATA);
	}
}

void MiaTOC::updateIdleness(void)
{
/*
	if( !isIdle && (difference >= 60*10)){
		isIdle = true;
		CString data;
		data.sprintf("toc_set_idle %i", difference);
		theSocket->writeData(data,SFLAP_TYPE_DATA);
	}
	
*/
}



void MiaTOC::tocInitDone(void)
{
	theSocket->writeData("toc_init_done",SFLAP_TYPE_DATA);
}

void MiaTOC::setConfig(void)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	CString conf, data;
	data.Format("toc_set_config \"%s\"", conf);
	if(data != lastConfigSent )
	{
		theSocket->writeData(data,SFLAP_TYPE_DATA);
		lastConfigSent = data;
	}
}

void MiaTOC::sendConfig(void)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}
}

void MiaTOC::tocremoveBuddy(const MiaBuddyList &a, const CString &buddyName)
{
	//MiaBuddyList newList = a;
	//currentConfig.buddyList = newList;
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	CString data;
	// remove buddy
	data = "toc_remove_buddy " + tocNormalize(buddyName);
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}

void MiaTOC::tocaddBuddy(const MiaBuddyList &a, const CString &buddyName)
{
	//MiaBuddyList newList = a;
	//currentConfig.buddyList = newList;
	
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}
	
	CString data;
	// remove buddy
	data = "toc_add_buddy " + tocNormalize(buddyName);
	theSocket->writeData(data,SFLAP_TYPE_DATA);
	//theSocket->writeData(data,SFLAP_TYPE_DATA);
}

void MiaTOC::sendPermissions(void)
{
	//int i;

	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}
	CString data;
	//set permit mode
	switch(lastPermissionSent)
	{
    case TOC_PERMITSOME:
    case TOC_PERMITALL:
		//theSocket->writeData("toc_add_permit digitalpeer",SFLAP_TYPE_DATA);
		theSocket->writeData("toc_add_permit",SFLAP_TYPE_DATA);
		break;
	case TOC_DENYALL:
	case TOC_DENYSOME:
		theSocket->writeData("toc_add_deny",SFLAP_TYPE_DATA);
		break;
	}
	/*
	switch(currentConfig.permitStatus)
	{
	case TOC_PERMITSOME:
		data = "toc_add_permit";
		//for(i = 0; i < currentConfig.permitList.getCount(); i++)
		//{
		//	data += " " + tocNormalize( currentConfig.permitList.getName(i) );
		//}
		theSocket->writeData(data,SFLAP_TYPE_DATA);
		break;
	case TOC_DENYALL:
		theSocket->writeData("toc_add_permit",SFLAP_TYPE_DATA);
		break;
	case TOC_DENYSOME:
		data = "toc_add_deny";
		//for(i = 0; i < currentConfig.denyList.getCount(); i++)
		//{
		//	data += " " + tocNormalize( currentConfig.denyList.getName(i) );
		//}
		theSocket->writeData(data,SFLAP_TYPE_DATA);
	case TOC_PERMITALL:
		theSocket->writeData("toc_add_deny",SFLAP_TYPE_DATA);
		break;
	}
	
	lastPermissionSent = currentConfig.permitStatus;
	*/
}

void MiaTOC::sendUserInfo(void)
{
	if(!theSocket)
	{
		AfxMessageBox("not connected, should be");
		return;
	}

	CString data;
	data.Format("toc_set_info %s", tocProcess(userInfo));
	if(data != lastInfoSent)
	{
		theSocket->writeData(data,SFLAP_TYPE_DATA);
		lastInfoSent = data;
	}
}

void MiaTOC::setMiaStatus(int theStatus)
{
	status = theStatus;
	
}

void MiaTOC::doUpdateBuddy(const CString &data)
{
	/*
	this is the format of the data comming in to update a buddy
	buddyname:T:0:1018390832:0: O
	*/

	CString thisBuddyName;
	int newStatus = MiaBuddyList::BUDDY_STATUS_OFFLINE;
	int newEvil = 0;;
	int newsignonTime = 0;
	int newidleTime = 0;
	int newbuddyClass;
	bool isAway = false;

	int i;
	
	CString workstr = data;
	
	//delete "UPDATE_BUDDY:"
	workstr.Delete(0, 13);
	
	//get the name of the buddy
	i = workstr.Find(':');				//find the first colon
	thisBuddyName = workstr.Left(i);
	thisBuddyName = tocNormalize(thisBuddyName);
	workstr.Delete(0, i + 1);			// skip past the colon
	
	//the status is either going to be a T or F
	if (workstr.GetAt(0) == 'T')
		newStatus = MiaBuddyList::BUDDY_STATUS_ONLINE;
		
	workstr.Delete(0, 2);				// skip the status and the colon
	
	//get the evil amount which is going to be from 0 to 100
	i = workstr.Find(':');				//find the colon
	CString buddyEvilStr = workstr.Left(i);			//save it to a string
	newEvil = atoi(buddyEvilStr.GetBuffer(buddyEvilStr.GetLength()));
	workstr.Delete(0, i + 1);			//delete up to and including the colon
	
	
	//signon time in seconds econds since unix epoch
	i = workstr.Find(':');			//find colon
	CString signonTimeStr = workstr.Left(i);
	newsignonTime = atoi(signonTimeStr.GetBuffer(signonTimeStr.GetLength()));
	workstr.Delete(0, i + 1);



	//get the idle time in minutes
	i = workstr.Find(':');				//find the first colon
	CString idleTimeStr = workstr.Left(i);
	newidleTime = atoi((LPCTSTR)idleTimeStr);
	workstr.Delete(0, i + 1);			//delete up to and including the colon
	
	

	CString buddyTypeFirstSlot;
	if (workstr.GetLength() >= 1)
		buddyTypeFirstSlot = workstr.GetAt(0);
	else
		buddyTypeFirstSlot = "-";
	
	CString buddyTypeSecondSlot;
	if (workstr.GetLength() >= 2)
		buddyTypeSecondSlot = workstr.GetAt(1);
	else
		buddyTypeSecondSlot = "-";
	
	CString buddyTypeThirdSlot;
	if (workstr.GetLength() >= 3)
		buddyTypeThirdSlot = workstr.GetAt(2);
	else
		buddyTypeThirdSlot = "-";


	// user class "A " == AOL  " A" == oscar admin  " U" == unconfirmed  " O" == normal
	if(buddyTypeFirstSlot == "A")
		newbuddyClass = MiaBuddyList::BUDDY_TYPE_AOL;
	else
	{
		if (buddyTypeSecondSlot == "A")
			newbuddyClass = MiaBuddyList::BUDDY_TYPE_ADMIN;
		else if (buddyTypeSecondSlot == "U")
			newbuddyClass = MiaBuddyList::BUDDY_TYPE_UNCONFIRMED;
		else if (buddyTypeSecondSlot == "O")
			newbuddyClass = MiaBuddyList::BUDDY_TYPE_NORMAL;


		if (buddyTypeThirdSlot == "U")
			newStatus = MiaBuddyList::BUDDY_STATUS_AWAY;
	}

	
	//now that I have the info, update buddy
	buddyList->refreshBuddyData(thisBuddyName,newStatus,newEvil,newsignonTime,
		newidleTime,newbuddyClass);
}

void MiaTOC::doNick(const CString &data)
{
	CString workstr = data;
	//delete "NICK:"
	workstr.Delete(0, 5);
}


void MiaTOC::doIM(const CString &data)
{
	
	CString workstr;
	CString senderName;
	bool isAuto;
	int i;
	
	workstr = data;
	
	//delete "IM_IN:"
	workstr.Delete(0, 6);
	
	// get username
	i = workstr.Find(':');
	
	// if no colons, then there's something wrong
	if(i == -1)
		return;
	else
	{
		senderName = workstr.Left(i);
		workstr.Delete(0, i + 1);
	}
	
	// get whether it's auto
	isAuto = (workstr.GetAt(0) == 'T' ) ? true : false;
	workstr.Delete(0, 2);
	
	//now let the main window handle the new IM
	myParentWindow->processNewMessage(senderName, workstr, isAuto);

}

//let the user know warning level was changed
void MiaTOC::doEviled(const CString &data)
{
	CString workstr;
	int newEvil;
	int i;
	
	workstr = data;
	// skip EVILED:
	workstr.Delete(0, 7);
	
	i = workstr.Find(':');
	if(i == -1)
		return;
	
	newEvil = atoi((LPCTSTR)workstr.Left(i));

	// remove new evil
	workstr.Delete(0, i + 1);

	// check if it's anonymous, and if it's a warning or a reduction
	if(newEvil > oldEvil)
	{
		myParentWindow->UpdateDebug(_T("Warning level reduced"));
	}
	else
	{
		myParentWindow->UpdateDebug(_T("Warning level increased"),true,true);
	}
}

//let the user know password was or was not changed
void MiaTOC::doPasswordMessage(const CString &data)
{
	CString work = data;
	work.Delete(0,20);
	if (work == "0")
	{
		CString passwordChangeGood = _T("Password updated successfully.");	
		myParentWindow->UpdateDebug(passwordChangeGood);
		AfxMessageBox(passwordChangeGood);
	}
	else
	{
		CString passwordChangeError = _T("Error in changing the password.");	
		myParentWindow->UpdateDebug(passwordChangeError);
		AfxMessageBox(passwordChangeError);
	}
}

void MiaTOC::doError(CString &data,bool killConnection)
{
	if (killConnection)
	{
		if(theSocket)
		{
			theSocket->Close();
		}
	}

	int errorno = 0;
	int i;
	CString workstr;
	CString message;
	CString display;
	
	workstr = data;
	
	// skip ERROR:
	workstr.Delete(0, 6);
	
	// extract error number
	// CString message used as a temporary here
	// after this, workstr holds the parameter
	i = workstr.Find(':');
	if(i != -1)
	{
		message = workstr.Left(i);
		errorno = atoi((LPCTSTR)message);
		workstr.Delete(0, i + 1);
	}
	else
	{
		errorno = atoi((LPCTSTR)workstr);
		workstr.Empty();
	}
	
	switch(errorno)
	{			
		case 901:
			doModalMessage("%s not currently available");
			break;
		case 902:
			doModalMessage("Warning of %s not currently available");
			break;
		case 903:
			doModalMessage("A message has been dropped, you are exceeding the server speed limit");
			break;
		case 950:
			doModalMessage("Chat in %s is unavailable.");
			break;
		case 960:
			doModalMessage("You are sending message too fast to %s");
			break;
		case 961:
			doModalMessage("Your missed an im from %s because it was too big.");
			break;
		case 962:
			doModalMessage("Your missed an im from %s because it was sent too fast.");
			break;
		case 970:
			doModalMessage("Failure");
			break;
		case 971:
			doModalMessage("Too many matches");
			break;
		case 972:
			doModalMessage("Need more qualifiers");
			break;
		case 973:
			doModalMessage("Dir service temporarily unavailable");
			break;
		case 974:
			doModalMessage("Email lookup restricted");
			break;
		case 975:
			doModalMessage("Keyword Ignored");
			break;
		case 976:
			doModalMessage("No Keywords");
			break;
		case 977:
			doModalMessage("Language not supported");
			break;
		case 978:
			doModalMessage("Country not supported");
			break;
		case 979:
			doModalMessage("Failure unknown %s");
			break;
		case 980:
			doModalMessage("Incorrect nickname or password");
			break;
		case 981:
			doModalMessage("The service is temporarily unavailable.");
			break;
		case 982:
			doModalMessage("Your warning level is currently too high to sign on.");
			break;
		case 983:
			doModalMessage("You have been connecting and disconnecting too frequently.  Wait 10 minutes and try again.  If you continue to try, you will need to wait even longer");
			break;
		case 989:
			doModalMessage("An unknown signon error has occured %s");
			break;
		default:
			doModalMessage("Unknown error code");
			break;
	}
}




/*
void MiaTOC::requestDirectory(const CString &target)
{
	if(!theSocket) return;
	//CString data = CString::fromLatin1("toc_get_dir %1").arg(tocNormalize(target));
	CString data;
	data.Format("toc_get_dir %1",tocNormalize(target));
	theSocket->writeData(data,SFLAP_TYPE_DATA);
	endIdleness();
}

void MiaTOC::setDirectory(const directory &dir)
{
	if(!theSocket) 
		return;
	
	CString data;
	data.Format("toc_set_dir %1:%2:%3:%4:%5:%6:%7:%8:",
		tocProcess(dir.firstName),tocProcess(dir.middleName),
		tocProcess(dir.lastName),tocProcess(dir.maidenName),
		tocProcess(dir.city),tocProcess(dir.state),
		tocProcess(dir.country),tocProcess(dir.email));


	if (dir.allowWebSearches)
		data += "T";

	theSocket->writeData(data,TYPE_DATA);
	endIdleness();
}

void MiaTOC::searchDirectory(const directory &dir)
{
	if(!theSocket)
		return;
	
	CString data;
	data.Format("toc_set_dir %1:%2:%3:%4:%5:%6:%7:%8:",
		tocProcess(dir.firstName),tocProcess(dir.middleName),
		tocProcess(dir.lastName),tocProcess(dir.maidenName),
		tocProcess(dir.city),tocProcess(dir.state),
		tocProcess(dir.country),tocProcess(dir.email));

	theSocket->writeData(data,TYPE_DATA);
}
*/


////////////////////////////////////GROUP CHAT STUFF////////////////////////////////

//NONE OF THE CHATROOM STUFF WORKS YET



//toc_chat_join <Exchange> <Chat Room Name>
void MiaTOC::chatJoin(CString name, int Exchange)
{
	if(!theSocket) 
		return;
	
	CString data;

	data.Format("toc_chat_join %i %s", Exchange, tocProcess(name));
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}

//toc_chat_send <Chat Room ID> <Message>
void MiaTOC::chatSend(int room, CString message)
{
	if(!theSocket) 
		return;
	
	CString data;
	
	data.Format("toc_chat_send %i %s", room, tocProcess(message));
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}


//toc_chat_whisper <Chat Room ID> <dst_user> <Message>
void MiaTOC::chatWhisper(int room, CString dst_bud, CString message)
{
	if(!theSocket)
		return;
	
	CString data;
	
	data.Format("toc_chat_whisper %i %s %s", room, tocProcess(dst_bud), tocProcess(message));
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}

//toc_chat_invite <Chat Room ID> <Invite Msg> <buddy1> [<buddy2> [<buddy3> [...]]]
void MiaTOC::chatInvite(int room, CString message, CString buddy)
{
	if(!theSocket)
		return;
	
	// tocProcess each buddy.
	CString data;
	int i = -1;
	CString newbuddylist = "";
	while (buddy.GetLength() > 0)
	{
		i = buddy.Find(",");
		if(i != -1 && i != 0)
		{
			newbuddylist += tocProcess(buddy.Left(i)) + " ";
			buddy.Delete(0, i + 2);
		}
		else
		{
			newbuddylist += tocProcess(buddy);
			buddy.Delete(0, buddy.GetLength());
		}
		
	}
	
	data.Format("toc_chat_invite %i %s %s", room, tocProcess(message), newbuddylist);
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}

//toc_chat_leave <Chat Room ID>
void MiaTOC::chatLeave(int room)
{
	if(!theSocket)
		return;
	
	CString data;
	data.Format("toc_chat_leave %i", room);
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}

//toc_chat_accept <Chat Room ID>
void MiaTOC::chatAccept(int room)
{
	if(!theSocket) return;
	
	CString data;
	data.Format("toc_chat_accept %i", room);
	theSocket->writeData(data,SFLAP_TYPE_DATA);
}


//CHAT_JOIN:<Chat Room Id>:<Chat Room Name>
void MiaTOC::doChatJoin(const CString &data)
{
	CString work = data;
	work.Delete(0,10);
	
	int i;
	int room = 0;
	CString name;
	
	i = work.Find(':');
	if(i != -1)
	{
		//room = (work.Left(i)).toInt();
		room = atoi((LPCTSTR)work.Left(i));
		name = work.Right(work.GetLength()-i-1);
	}
	//chat_joined(room,name);
}

//CHAT_IN:<Chat Room Id>:<Source User>:<Whisper? T/F>:<Message>
void MiaTOC::doChatIn(const CString &data)
{
	CString work = data;
	work.Delete(0,8);
	
	int i;
	int room = 0;
	CString buddy;
	bool wisper;
	CString message;
	
	i = work.Find(':');
	if(i != -1)
	{
		//room = (work.Left(i)).toInt();
		room = atoi((LPCTSTR)work.Left(i));
		work = work.Right(work.GetLength()-i-1);
	}
	
	i = work.Find(':');
	if(i != -1)
	{
		buddy = work.Left(i);
		work = work.Right(work.GetLength()-i-1);
	}
	wisper = (work.GetAt(0) == 'T') ? true : false;
	message = work.Mid(2, work.GetLength()-2);
	//chat_in(room, buddy, wisper, message);
}

//CHAT_UPDATE_BUDDY:<Chat Room Id>:<Inside? T/F>:<User 1>:<User 2>...
void MiaTOC::doChatUpdateBuddy(const CString &data)
{
	CString work = data;
	work.Delete(0,18);
	
	int i;
	int room = 0;
	bool inside;
	CString buddy;
	
	i = work.Find(':');
	if(i != -1)
	{
		//room = (work.Left(i)).toInt();
		room = atoi((LPCTSTR)work.Left(i));
		work = work.Right(work.GetLength()-i-1);
	}
	inside = (work.GetAt(0) == 'T' ) ? true : false;
	work = work.Mid(2, work.GetLength()-2);
	while (i != -1)
	{
		i = work.Find(':');
		if(i != -1)
		{
			buddy = work.Left(i);
			work = work.Right(work.GetLength()-i-1);
		}
		else
		{
			if (work.GetLength() > 0)
			{
				//chat_updateBuddy(room, inside, work);
			}
		}
	}
}

//CHAT_INVITE:<Chat Room Name>:<Chat Room Id>:<Invite Sender>:<Message>
void MiaTOC::doChatInvite(const CString &data)
{
	CString work = data;
	work.Delete(0,12);
	
	int i;
	
	CString name = "Mia Error";
	int room = 0;
	CString buddy;
	CString message;
	
	i = work.Find(':');
	if(i != -1)
	{
		name = work.Left(i);
		work = work.Right(work.GetLength()-i-1);
	}
	i = work.Find(':');
	if(i != -1)
	{
		room = atoi((LPCTSTR)work.Left(i));
		work = work.Right(work.GetLength()-i-1);
	}
	i = work.Find(':');
	if(i != -1)
	{
		buddy = work.Left(i);
		message = work.Right(work.GetLength()-i-1);
	}
	//chat_invite(name,room,buddy,message);
}

//CHAT_LEFT:<Chat Room Id>
void MiaTOC::doChatLeft(const CString &data)
{
	CString work = data;
	work.Delete(0,10);
	//int roomLeft = work.toInt();
	int roomLeft = atoi((LPCTSTR)work);
	//chat_left(roomLeft);
}



