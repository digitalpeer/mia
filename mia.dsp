# Microsoft Developer Studio Project File - Name="mia" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=mia - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mia.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mia.mak" CFG="mia - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mia - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "mia - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mia - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "mia - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "mia - Win32 Release"
# Name "mia - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\htmlctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Mia.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaAboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaAddBuddyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaAddGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaAwayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaBuddy.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaBuddyList.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaChatDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaChatRoomDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaCreateChatRoom.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaDebugWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaEditInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaFileFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaMainWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaNumberTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaProtocolIRC.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaSendTextBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaSystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaTOC.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaVewTextBox.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\htmlctrl.h
# End Source File
# Begin Source File

SOURCE=.\Mia.h
# End Source File
# Begin Source File

SOURCE=.\MiaAboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\MiaAddBuddyDlg.h
# End Source File
# Begin Source File

SOURCE=.\MiaAddGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\MiaAwayDlg.h
# End Source File
# Begin Source File

SOURCE=.\MiaBuddy.h
# End Source File
# Begin Source File

SOURCE=.\MiaBuddyList.h
# End Source File
# Begin Source File

SOURCE=.\MiaChatDialog.h
# End Source File
# Begin Source File

SOURCE=.\MiaChatRoomDlg.h
# End Source File
# Begin Source File

SOURCE=.\MiaConfig.h
# End Source File
# Begin Source File

SOURCE=.\MiaCreateChatRoom.h
# End Source File
# Begin Source File

SOURCE=.\MiaDebugWindow.h
# End Source File
# Begin Source File

SOURCE=.\MiaEditInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\MiaFileFunc.h
# End Source File
# Begin Source File

SOURCE=.\MiaInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\MiaMainWindow.h
# End Source File
# Begin Source File

SOURCE=.\MiaNumberTrack.h
# End Source File
# Begin Source File

SOURCE=.\MiaProtocolIRC.h
# End Source File
# Begin Source File

SOURCE=.\MiaSendTextBox.h
# End Source File
# Begin Source File

SOURCE=.\MiaSocket.h
# End Source File
# Begin Source File

SOURCE=.\MiaSystemTray.h
# End Source File
# Begin Source File

SOURCE=.\MiaTOC.h
# End Source File
# Begin Source File

SOURCE=.\MiaVector.h
# End Source File
# Begin Source File

SOURCE=.\MiaViewTextBox.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Graphics"

# PROP Default_Filter "gif,bmp,jpg"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\graphics\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\btn_delb.bmp
# End Source File
# Begin Source File

SOURCE=.\BTNLAWAY.bmp
# End Source File
# Begin Source File

SOURCE=.\graphics\BTNLAWAY.bmp
# End Source File
# Begin Source File

SOURCE=.\BTNLAWAYDOWN.BMP
# End Source File
# Begin Source File

SOURCE=.\graphics\BTNLAWAYDOWN.BMP
# End Source File
# Begin Source File

SOURCE=.\BTNLNEWCHAT.bmp
# End Source File
# Begin Source File

SOURCE=.\graphics\BTNLNEWCHAT.bmp
# End Source File
# Begin Source File

SOURCE=".\BTNLNEWCHATDOWN copy.bmp"
# End Source File
# Begin Source File

SOURCE=".\Graphics\BTNLNEWCHATDOWN copy.bmp"
# End Source File
# Begin Source File

SOURCE=.\graphics\BTNLNEWCHATDOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\graphics\BUDDYLISTLOGO.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\dtn_addb.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\LOGONLOGO.bmp
# End Source File
# Begin Source File

SOURCE=.\graphics\mainlogo256.bmp
# End Source File
# Begin Source File

SOURCE=.\mainlogo256.bmp
# End Source File
# Begin Source File

SOURCE=.\graphics\OKD.BMP
# End Source File
# Begin Source File

SOURCE=.\graphics\OKF.BMP
# End Source File
# Begin Source File

SOURCE=.\graphics\OKU.BMP
# End Source File
# Begin Source File

SOURCE=.\graphics\SIGNOFF.bmp
# End Source File
# Begin Source File

SOURCE=.\SIGNOFF.bmp
# End Source File
# Begin Source File

SOURCE=.\graphics\SIGNOFFDOWN.bmp
# End Source File
# Begin Source File

SOURCE=.\SIGNOFFDOWN.bmp
# End Source File
# End Group
# Begin Group "Icons"

# PROP Default_Filter "ico"
# Begin Source File

SOURCE=.\favicon.ico
# End Source File
# Begin Source File

SOURCE=.\icons\favicon.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\mainicon.ico
# End Source File
# Begin Source File

SOURCE=.\icons\mia.ico
# End Source File
# Begin Source File

SOURCE=.\mia.ico
# End Source File
# Begin Source File

SOURCE=.\Icons\POSTITL.ICO
# End Source File
# Begin Source File

SOURCE=.\Icons\snapin.Ico
# End Source File
# Begin Source File

SOURCE=.\icons\soaf.ico
# End Source File
# Begin Source File

SOURCE=.\soaf.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# End Group
# Begin Group "PropertyDlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MiaPropertyAwayIdle.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyAwayIdle.h
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyBuddyList.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyBuddyList.h
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyLogging.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyLogging.h
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyPageNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyPageNetwork.h
# End Source File
# Begin Source File

SOURCE=.\MiaPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyUser.cpp
# End Source File
# Begin Source File

SOURCE=.\MiaPropertyUser.h
# End Source File
# End Group
# End Target
# End Project
