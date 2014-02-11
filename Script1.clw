; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=MiaPropertyAwayIdle
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "script1.h"
LastPage=0

ClassCount=16
Class1=CSystemTray

ResourceCount=22
Resource1=PROPERTIES
Resource2=IDR_MENU_BUDDY
Resource3=IDD_INFO
Resource4=IDD_ADDGROUP
Resource5=PROPERTIES_NETWORK
Resource6=IDD_SIGNON
Resource7=IDD_DIALOG5
Resource8=IDD_DIALOG2
Resource9=IDR_MENU_TRAY
Resource10=IDD_AWAYMESSAGE
Class2=MiaSignonDlg
Class3=MiaAboutDlg
Class4=MiaAwayDlg
Resource11=IDD_ADDBUDDY
Class5=test
Resource12=PROPERTIES_BUDDYLIST
Class6=MiaEditInfoDlg
Class7=MiaInfoDlg
Resource13=IDR_MENU_STATUS
Resource14=IDD_ABOUT
Class8=MiaAddGroupDlg
Class9=MiaAddBuddyDlg
Resource15=IDR_MENU_MAIN
Resource16=IDD_CREATECHATROOM
Resource17=IDD_EDITINFO
Resource18=PROPERTIES_USER
Class10=MiaPropertyLogging
Class11=MiaPropertyBuddyList
Class12=MiaPropertyUser
Class13=MiaPropertyPageNetwork
Class14=MiaPropertySheet
Resource19=PROPERTIES_LOGGING
Class15=MiaCreateChatRoom
Resource20=IDR_MENU_DEBUG
Resource21=IDR_MENU_CHAT
Class16=MiaPropertyAwayIdle
Resource22=PROPERTIES_AWAYANDIDLE

[CLS:CSystemTray]
Type=0
BaseClass=CWnd
HeaderFile=MiaSystemTray.h
ImplementationFile=MiaSystemTray.cpp
LastObject=CSystemTray

[MNU:IDR_MENU_BUDDY]
Type=1
Class=?
Command1=ID_TOP_BUDDYNAME
Command2=ID_TOP_IDLETIME
Command3=ID_TOP_ONLINETIME
Command4=ID_TOP_WARNINGLEVEL
Command5=ID_TOP_SERVICE
Command6=ID_TOP_GETUSERINFO
Command7=ID_TOP_INVITETOCHAT
Command8=ID_TOP_SENDMESSAGE
Command9=ID_TOP_BLOCKBUDDY
Command10=ID_TOP_COPYBUDDYNAMETOCLIPBOARD
CommandCount=10

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=ID_MIA_AWAYMESSAGE
Command2=ID_EDITINFO
Command3=ID_MIA_EDITOPTIONS_PREFERENCES
Command4=ID_OPTIONS_CHANGEPASSWORD
Command5=ID_MIA_EDITOPTIONS_DELETEALLLOGFILES
Command6=ID_MIA_DEBUGWINDOW
Command7=ID_MIA_CLOSEALLWINDOWS
Command8=ID_MIA_SHOWALLWINDOWS
Command9=ID_MIA_MINIMIZEALLWINDOWS
Command10=ID_MIA_SHOWMAINWINDOW
Command11=ID_MIA_MINIMIZEMAINWINDOW
Command12=ID_MIA_WINDOWS_KEEPBUDDYLISTONTOP
Command13=ID_MIA_LOADLIST
Command14=ID_MIA_SAVELIST
Command15=ID_MIA_SIGNONSIGNOFF
Command16=ID_MIA_EXIT
Command17=ID_ABOUT_ABOUTMIA
Command18=ID_ABOUT_HELP
Command19=ID_ABOUT_FEEDBACK
CommandCount=19

[MNU:IDR_MENU_CHAT]
Type=1
Class=?
Command1=ID_CHAT_FILE_LOAD
Command2=ID_CHAT_FILE_SAVE
Command3=ID_CHAT_FILE_EXIT
Command4=ID_CHAT_OPTIONS_BLOCKBUDDY
Command5=ID_CHAT_OPTIONS_WARNBUDDY
CommandCount=5

[MNU:IDR_MENU_TRAY]
Type=1
Class=?
Command1=ID_MIA_EDITOPTIONS_PREFERENCES
Command2=ID_OPTIONS_CHANGEPASSWORD
Command3=ID_MIA_AWAYMESSAGE
Command4=ID_EDITINFO
Command5=ID_MIA_DEBUGWINDOW
Command6=ID_MIA_CLOSEALLWINDOWS
Command7=ID_MIA_SHOWALLWINDOWS
Command8=ID_MIA_MINIMIZEALLWINDOWS
Command9=ID_MIA_SHOWMAINWINDOW
Command10=ID_MIA_MINIMIZEMAINWINDOW
Command11=ID_MIA_WINDOWS_KEEPBUDDYLISTONTOP
Command12=ID_MIA_LOADLIST
Command13=ID_MIA_SAVELIST
Command14=ID_MIA_SIGNONSIGNOFF
Command15=ID_MIA_EXIT
CommandCount=15

[MNU:IDR_MENU_DEBUG]
Type=1
Class=?
Command1=ID_SAVE
Command2=ID_LOAD
Command3=ID_DEBUG_EXIT
CommandCount=3

[DLG:IDD_ABOUT]
Type=1
Class=MiaAboutDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1352730756

[CLS:MiaSignonDlg]
Type=0
HeaderFile=miasignondlg.h
ImplementationFile=miasignondlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_ABOUTMIA
VirtualFilter=dWC

[CLS:MiaAboutDlg]
Type=0
HeaderFile=miaaboutdlg.h
ImplementationFile=miaaboutdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_ABOUTMIA
VirtualFilter=dWC

[DLG:IDD_SIGNON]
Type=1
Class=MiaSignonDlg
ControlCount=11
Control1=IDC_USERNAME,combobox,1344340226
Control2=IDC_PASSWORD,edit,1350631456
Control3=IDC_SIGNON,button,1342242817
Control4=IDC_SAVEPASSWORD,button,1476460547
Control5=IDC_AUTOLOGIN,button,1476460547
Control6=IDC_OPTIONS,button,1342242816
Control7=IDC_STATIC,static,1342308364
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATUS,static,1342308865
Control10=IDC_SHOWDEBUG,button,1342242816
Control11=IDC_ENABLELOGGING,button,1342242819

[DLG:IDD_AWAYMESSAGE]
Type=1
Class=MiaAwayDlg
ControlCount=3
Control1=IDB_AWAYTOGGLE,button,1342242817
Control2=IDC_AWAYMESSAGEEDIT,edit,1350635716
Control3=IDC_STATIC,static,1342308352

[CLS:MiaAwayDlg]
Type=0
HeaderFile=MiaAwayDlg.h
ImplementationFile=MiaAwayDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDB_AWAYTOGGLE
VirtualFilter=dWC

[DLG:IDD_INFO]
Type=1
Class=MiaInfoDlg
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_HTMLVIEW,edit,1350631552
Control3=IDC_GETINFOSTATUS,static,1342308352

[DLG:IDD_EDITINFO]
Type=1
Class=MiaEditInfoDlg
ControlCount=5
Control1=ID_SAVEINFO,button,1342242816
Control2=ID_CANCELINFO,button,1342242816
Control3=IDC_RICHEDIT1,RICHEDIT,1350635716
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:MiaEditInfoDlg]
Type=0
HeaderFile=MiaEditInfoDlg.h
ImplementationFile=MiaEditInfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=MiaEditInfoDlg

[CLS:test]
Type=0
HeaderFile=test.h
ImplementationFile=test.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_ABOUTMIA

[CLS:MiaInfoDlg]
Type=0
HeaderFile=MiaInfoDlg.h
ImplementationFile=MiaInfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_ABOUT_ABOUTMIA

[DLG:IDD_ADDGROUP]
Type=1
Class=MiaAddGroupDlg
ControlCount=4
Control1=ID_ADD,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_ADDBUDDY]
Type=1
Class=MiaAddBuddyDlg
ControlCount=6
Control1=ID_ADD,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344340226
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:MiaAddGroupDlg]
Type=0
HeaderFile=MiaAddGroupDlg.h
ImplementationFile=MiaAddGroupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ADD
VirtualFilter=dWC

[CLS:MiaAddBuddyDlg]
Type=0
HeaderFile=MiaAddBuddyDlg.h
ImplementationFile=MiaAddBuddyDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_ABOUT_ABOUTMIA

[DLG:IDD_DIALOG2]
Type=1
Class=?
ControlCount=9
Control1=IDC_BUTTON3,button,1342275584
Control2=IDC_BUTTON4,button,1342275584
Control3=IDC_BUTTON5,button,1342275584
Control4=IDC_BUTTON6,button,1342275584
Control5=IDC_BUTTON7,button,1342275584
Control6=IDC_BUTTON8,button,1342275584
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1350701056
Control9=IDC_EDIT1,edit,1342244996

[MNU:IDR_MENU_STATUS]
Type=1
Class=?
Command1=ID_MIA_STATUS_SIGNOFF
Command2=ID_MIA_STATUS_SIGNON
Command3=ID_MIA_STATUS_IDLE
Command4=ID_MIA_STATUS_AWAY
CommandCount=4

[DLG:PROPERTIES]
Type=1
Class=?
ControlCount=0

[DLG:PROPERTIES_NETWORK]
Type=1
Class=MiaPropertyPageNetwork
ControlCount=6
Control1=IDC_P_TOCHOST,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_P_TOCPORT,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_P_RESETNETWORKDEFAULT,button,1342242816
Control6=IDC_STATIC,button,1342177287

[DLG:PROPERTIES_BUDDYLIST]
Type=1
Class=MiaPropertyBuddyList
ControlCount=12
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO1,button,1342177289
Control4=IDC_RADIO3,button,1342177289
Control5=IDC_KEEYBUDDYLISTONTOP,button,1342242819
Control6=IDC_LIST1,listbox,1352728835
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BUDDYLISTFONT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_ADDBLOCKEDBUDDY,button,1342242816
Control12=IDC_STATIC,button,1342177287

[DLG:PROPERTIES_LOGGING]
Type=1
Class=MiaPropertyLogging
ControlCount=5
Control1=IDC_P_ENABLEAIMCHATLOGGING,button,1342246915
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_LOGDIR,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[DLG:PROPERTIES_USER]
Type=1
Class=MiaPropertyUser
ControlCount=5
Control1=IDC_P_TOCUSERNAME,combobox,1344340226
Control2=IDC_P_TOCPASSWORD,edit,1350631456
Control3=IDC_STATIC,static,1342308364
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287

[CLS:MiaPropertyUser]
Type=0
HeaderFile=MiaPropertyUser.h
ImplementationFile=MiaPropertyUser.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=ID_ABOUT_ABOUTMIA

[CLS:MiaPropertyBuddyList]
Type=0
HeaderFile=MiaPropertyBuddyList.h
ImplementationFile=MiaPropertyBuddyList.cpp
BaseClass=CPropertyPage
Filter=D

[CLS:MiaPropertyLogging]
Type=0
HeaderFile=MiaPropertyLogging.h
ImplementationFile=MiaPropertyLogging.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=ID_ABOUT_ABOUTMIA

[CLS:MiaPropertyPageNetwork]
Type=0
HeaderFile=MiaPropertyPageNetwork.h
ImplementationFile=MiaPropertyPageNetwork.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=MiaPropertyPageNetwork
VirtualFilter=idWC

[CLS:MiaPropertySheet]
Type=0
HeaderFile=MiaPropertySheet.h
ImplementationFile=MiaPropertySheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=MiaPropertySheet
VirtualFilter=hWC

[DLG:IDD_DIALOG5]
Type=1
Class=?
ControlCount=4
Control1=IDC_RICHEDIT1,RICHEDIT,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDC_RICHEDIT2,RICHEDIT,1350631552

[DLG:IDD_CREATECHATROOM]
Type=1
Class=MiaCreateChatRoom
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1352732804
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:MiaCreateChatRoom]
Type=0
HeaderFile=MiaCreateChatRoom.h
ImplementationFile=MiaCreateChatRoom.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_ABOUT_ABOUTMIA

[DLG:PROPERTIES_AWAYANDIDLE]
Type=1
Class=MiaPropertyAwayIdle
ControlCount=9
Control1=IDC_EDIT1,edit,1352728708
Control2=IDC_IDLEMESSAGE,edit,1352732804
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_LIST1,listbox,1352728835
Control6=IDC_ADDNEWMESSAGE,button,1342242816
Control7=IDC_EDIT3,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:MiaPropertyAwayIdle]
Type=0
HeaderFile=MiaPropertyAwayIdle.h
ImplementationFile=MiaPropertyAwayIdle.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_LIST1

