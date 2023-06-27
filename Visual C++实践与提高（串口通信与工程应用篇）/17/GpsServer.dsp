# Microsoft Developer Studio Project File - Name="GpsServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GpsServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GpsServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GpsServer.mak" CFG="GpsServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GpsServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GpsServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GpsServer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "GpsServer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib mpr.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GpsServer - Win32 Release"
# Name "GpsServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "RS-cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RSComConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\RSUser.cpp
# End Source File
# End Group
# Begin Group "View-cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgComConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewComData.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewLog.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewNemaData.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewReceiveData.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewReceivePosition.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewSendData.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewTreeCom.cpp
# End Source File
# End Group
# Begin Group "COM-cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ComWorkFlow.cpp
# End Source File
# Begin Source File

SOURCE=.\DataFlow.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSPublic.cpp
# End Source File
# Begin Source File

SOURCE=.\ThreadCom.cpp
# End Source File
# End Group
# Begin Group "CJ60-cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CJButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CJControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CJTabctrlBar.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\GpsServer.cpp
# End Source File
# Begin Source File

SOURCE=.\GpsServer.rc
# End Source File
# Begin Source File

SOURCE=.\GpsServerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GpsServerView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "View-h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgComConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.h
# End Source File
# Begin Source File

SOURCE=.\ViewBase.h
# End Source File
# Begin Source File

SOURCE=.\ViewComData.h
# End Source File
# Begin Source File

SOURCE=.\ViewLog.h
# End Source File
# Begin Source File

SOURCE=.\ViewNemaData.h
# End Source File
# Begin Source File

SOURCE=.\ViewReceiveData.h
# End Source File
# Begin Source File

SOURCE=.\ViewReceivePosition.h
# End Source File
# Begin Source File

SOURCE=.\ViewSendData.h
# End Source File
# Begin Source File

SOURCE=.\ViewTreeCom.h
# End Source File
# End Group
# Begin Group "COM-h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ComWorkFlow.h
# End Source File
# Begin Source File

SOURCE=.\DataFlow.h
# End Source File
# Begin Source File

SOURCE=.\GPSPublic.h
# End Source File
# Begin Source File

SOURCE=.\ThreadCom.h
# End Source File
# End Group
# Begin Group "RS-h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RSComConfig.h
# End Source File
# Begin Source File

SOURCE=.\RSUser.h
# End Source File
# End Group
# Begin Group "CJ60-h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CJButton.h
# End Source File
# Begin Source File

SOURCE=.\CJControlBar.h
# End Source File
# Begin Source File

SOURCE=.\CJTabCtrlBar.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GpsServer.h
# End Source File
# Begin Source File

SOURCE=.\GpsServerDoc.h
# End Source File
# Begin Source File

SOURCE=.\GpsServerView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PUBLIC.H
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\GpsServer.ico
# End Source File
# Begin Source File

SOURCE=.\res\GpsServer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section GpsServer : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
