# Microsoft Developer Studio Generated NMAKE File, Based on GpsServer.dsp
!IF "$(CFG)" == ""
CFG=GpsServer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to GpsServer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GpsServer - Win32 Release" && "$(CFG)" != "GpsServer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "GpsServer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\GpsServer.exe" "$(OUTDIR)\GpsServer.bsc"


CLEAN :
	-@erase "$(INTDIR)\CJButton.obj"
	-@erase "$(INTDIR)\CJButton.sbr"
	-@erase "$(INTDIR)\CJComboBox.obj"
	-@erase "$(INTDIR)\CJComboBox.sbr"
	-@erase "$(INTDIR)\CJControlBar.obj"
	-@erase "$(INTDIR)\CJControlBar.sbr"
	-@erase "$(INTDIR)\CJDockBar.obj"
	-@erase "$(INTDIR)\CJDockBar.sbr"
	-@erase "$(INTDIR)\CJFrameWnd.obj"
	-@erase "$(INTDIR)\CJFrameWnd.sbr"
	-@erase "$(INTDIR)\CJMDIFrameWnd.obj"
	-@erase "$(INTDIR)\CJMDIFrameWnd.sbr"
	-@erase "$(INTDIR)\CJOutlookBar.obj"
	-@erase "$(INTDIR)\CJOutlookBar.sbr"
	-@erase "$(INTDIR)\CJPagerCtrl.obj"
	-@erase "$(INTDIR)\CJPagerCtrl.sbr"
	-@erase "$(INTDIR)\CJTabctrlBar.obj"
	-@erase "$(INTDIR)\CJTabctrlBar.sbr"
	-@erase "$(INTDIR)\CJToolBar.obj"
	-@erase "$(INTDIR)\CJToolBar.sbr"
	-@erase "$(INTDIR)\ComWorkFlow.obj"
	-@erase "$(INTDIR)\ComWorkFlow.sbr"
	-@erase "$(INTDIR)\CoolBar.obj"
	-@erase "$(INTDIR)\CoolBar.sbr"
	-@erase "$(INTDIR)\COOLMENU.OBJ"
	-@erase "$(INTDIR)\COOLMENU.SBR"
	-@erase "$(INTDIR)\DataFlow.obj"
	-@erase "$(INTDIR)\DataFlow.sbr"
	-@erase "$(INTDIR)\DlgComConfig.obj"
	-@erase "$(INTDIR)\DlgComConfig.sbr"
	-@erase "$(INTDIR)\DlgComData.obj"
	-@erase "$(INTDIR)\DlgComData.sbr"
	-@erase "$(INTDIR)\DlgLogin.obj"
	-@erase "$(INTDIR)\DlgLogin.sbr"
	-@erase "$(INTDIR)\GfxGroupEdit.obj"
	-@erase "$(INTDIR)\GfxGroupEdit.sbr"
	-@erase "$(INTDIR)\GfxOutBarCtrl.obj"
	-@erase "$(INTDIR)\GfxOutBarCtrl.sbr"
	-@erase "$(INTDIR)\GfxPopupMenu.obj"
	-@erase "$(INTDIR)\GfxPopupMenu.sbr"
	-@erase "$(INTDIR)\GpsServer.obj"
	-@erase "$(INTDIR)\GpsServer.pch"
	-@erase "$(INTDIR)\GpsServer.res"
	-@erase "$(INTDIR)\GpsServer.sbr"
	-@erase "$(INTDIR)\GpsServerDoc.obj"
	-@erase "$(INTDIR)\GpsServerDoc.sbr"
	-@erase "$(INTDIR)\GpsServerView.obj"
	-@erase "$(INTDIR)\GpsServerView.sbr"
	-@erase "$(INTDIR)\hyperlink.obj"
	-@erase "$(INTDIR)\hyperlink.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\NEMA0183Parse.obj"
	-@erase "$(INTDIR)\NEMA0183Parse.sbr"
	-@erase "$(INTDIR)\NEMA0183Sentence.obj"
	-@erase "$(INTDIR)\NEMA0183Sentence.sbr"
	-@erase "$(INTDIR)\NEMAGPGGA.obj"
	-@erase "$(INTDIR)\NEMAGPGGA.sbr"
	-@erase "$(INTDIR)\PUBLIC.OBJ"
	-@erase "$(INTDIR)\PUBLIC.SBR"
	-@erase "$(INTDIR)\RSComConfig.obj"
	-@erase "$(INTDIR)\RSComConfig.sbr"
	-@erase "$(INTDIR)\RSOper.obj"
	-@erase "$(INTDIR)\RSOper.sbr"
	-@erase "$(INTDIR)\RSOperType.obj"
	-@erase "$(INTDIR)\RSOperType.sbr"
	-@erase "$(INTDIR)\RSUser.obj"
	-@erase "$(INTDIR)\RSUser.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\SUBCLASS.OBJ"
	-@erase "$(INTDIR)\SUBCLASS.SBR"
	-@erase "$(INTDIR)\ThreadCom.obj"
	-@erase "$(INTDIR)\ThreadCom.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\ViewLog.obj"
	-@erase "$(INTDIR)\ViewLog.sbr"
	-@erase "$(INTDIR)\ViewNEMADecode.obj"
	-@erase "$(INTDIR)\ViewNEMADecode.sbr"
	-@erase "$(INTDIR)\ViewRecvContent.obj"
	-@erase "$(INTDIR)\ViewRecvContent.sbr"
	-@erase "$(INTDIR)\ViewSend.obj"
	-@erase "$(INTDIR)\ViewSend.sbr"
	-@erase "$(INTDIR)\ViewTreeCom.obj"
	-@erase "$(INTDIR)\ViewTreeCom.sbr"
	-@erase "$(OUTDIR)\GpsServer.bsc"
	-@erase "$(OUTDIR)\GpsServer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\GpsServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\GpsServer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GpsServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CJButton.sbr" \
	"$(INTDIR)\CJComboBox.sbr" \
	"$(INTDIR)\CJControlBar.sbr" \
	"$(INTDIR)\CJDockBar.sbr" \
	"$(INTDIR)\CJFrameWnd.sbr" \
	"$(INTDIR)\CJMDIFrameWnd.sbr" \
	"$(INTDIR)\CJOutlookBar.sbr" \
	"$(INTDIR)\CJPagerCtrl.sbr" \
	"$(INTDIR)\CJTabctrlBar.sbr" \
	"$(INTDIR)\CJToolBar.sbr" \
	"$(INTDIR)\CoolBar.sbr" \
	"$(INTDIR)\COOLMENU.SBR" \
	"$(INTDIR)\GfxGroupEdit.sbr" \
	"$(INTDIR)\GfxOutBarCtrl.sbr" \
	"$(INTDIR)\GfxPopupMenu.sbr" \
	"$(INTDIR)\hyperlink.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\SUBCLASS.SBR" \
	"$(INTDIR)\RSComConfig.sbr" \
	"$(INTDIR)\RSOper.sbr" \
	"$(INTDIR)\RSOperType.sbr" \
	"$(INTDIR)\RSUser.sbr" \
	"$(INTDIR)\DlgComConfig.sbr" \
	"$(INTDIR)\DlgComData.sbr" \
	"$(INTDIR)\DlgLogin.sbr" \
	"$(INTDIR)\ViewLog.sbr" \
	"$(INTDIR)\ViewNEMADecode.sbr" \
	"$(INTDIR)\ViewRecvContent.sbr" \
	"$(INTDIR)\ViewSend.sbr" \
	"$(INTDIR)\ViewTreeCom.sbr" \
	"$(INTDIR)\ComWorkFlow.sbr" \
	"$(INTDIR)\DataFlow.sbr" \
	"$(INTDIR)\ThreadCom.sbr" \
	"$(INTDIR)\NEMA0183Parse.sbr" \
	"$(INTDIR)\NEMA0183Sentence.sbr" \
	"$(INTDIR)\NEMAGPGGA.sbr" \
	"$(INTDIR)\GpsServer.sbr" \
	"$(INTDIR)\GpsServerDoc.sbr" \
	"$(INTDIR)\GpsServerView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\PUBLIC.SBR" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\GpsServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\GpsServer.pdb" /machine:I386 /out:"$(OUTDIR)\GpsServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CJButton.obj" \
	"$(INTDIR)\CJComboBox.obj" \
	"$(INTDIR)\CJControlBar.obj" \
	"$(INTDIR)\CJDockBar.obj" \
	"$(INTDIR)\CJFrameWnd.obj" \
	"$(INTDIR)\CJMDIFrameWnd.obj" \
	"$(INTDIR)\CJOutlookBar.obj" \
	"$(INTDIR)\CJPagerCtrl.obj" \
	"$(INTDIR)\CJTabctrlBar.obj" \
	"$(INTDIR)\CJToolBar.obj" \
	"$(INTDIR)\CoolBar.obj" \
	"$(INTDIR)\COOLMENU.OBJ" \
	"$(INTDIR)\GfxGroupEdit.obj" \
	"$(INTDIR)\GfxOutBarCtrl.obj" \
	"$(INTDIR)\GfxPopupMenu.obj" \
	"$(INTDIR)\hyperlink.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\SUBCLASS.OBJ" \
	"$(INTDIR)\RSComConfig.obj" \
	"$(INTDIR)\RSOper.obj" \
	"$(INTDIR)\RSOperType.obj" \
	"$(INTDIR)\RSUser.obj" \
	"$(INTDIR)\DlgComConfig.obj" \
	"$(INTDIR)\DlgComData.obj" \
	"$(INTDIR)\DlgLogin.obj" \
	"$(INTDIR)\ViewLog.obj" \
	"$(INTDIR)\ViewNEMADecode.obj" \
	"$(INTDIR)\ViewRecvContent.obj" \
	"$(INTDIR)\ViewSend.obj" \
	"$(INTDIR)\ViewTreeCom.obj" \
	"$(INTDIR)\ComWorkFlow.obj" \
	"$(INTDIR)\DataFlow.obj" \
	"$(INTDIR)\ThreadCom.obj" \
	"$(INTDIR)\NEMA0183Parse.obj" \
	"$(INTDIR)\NEMA0183Sentence.obj" \
	"$(INTDIR)\NEMAGPGGA.obj" \
	"$(INTDIR)\GpsServer.obj" \
	"$(INTDIR)\GpsServerDoc.obj" \
	"$(INTDIR)\GpsServerView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PUBLIC.OBJ" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\GpsServer.res"

"$(OUTDIR)\GpsServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GpsServer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\GpsServer.exe" "$(OUTDIR)\GpsServer.bsc"


CLEAN :
	-@erase "$(INTDIR)\CJButton.obj"
	-@erase "$(INTDIR)\CJButton.sbr"
	-@erase "$(INTDIR)\CJComboBox.obj"
	-@erase "$(INTDIR)\CJComboBox.sbr"
	-@erase "$(INTDIR)\CJControlBar.obj"
	-@erase "$(INTDIR)\CJControlBar.sbr"
	-@erase "$(INTDIR)\CJDockBar.obj"
	-@erase "$(INTDIR)\CJDockBar.sbr"
	-@erase "$(INTDIR)\CJFrameWnd.obj"
	-@erase "$(INTDIR)\CJFrameWnd.sbr"
	-@erase "$(INTDIR)\CJMDIFrameWnd.obj"
	-@erase "$(INTDIR)\CJMDIFrameWnd.sbr"
	-@erase "$(INTDIR)\CJOutlookBar.obj"
	-@erase "$(INTDIR)\CJOutlookBar.sbr"
	-@erase "$(INTDIR)\CJPagerCtrl.obj"
	-@erase "$(INTDIR)\CJPagerCtrl.sbr"
	-@erase "$(INTDIR)\CJTabctrlBar.obj"
	-@erase "$(INTDIR)\CJTabctrlBar.sbr"
	-@erase "$(INTDIR)\CJToolBar.obj"
	-@erase "$(INTDIR)\CJToolBar.sbr"
	-@erase "$(INTDIR)\ComWorkFlow.obj"
	-@erase "$(INTDIR)\ComWorkFlow.sbr"
	-@erase "$(INTDIR)\CoolBar.obj"
	-@erase "$(INTDIR)\CoolBar.sbr"
	-@erase "$(INTDIR)\COOLMENU.OBJ"
	-@erase "$(INTDIR)\COOLMENU.SBR"
	-@erase "$(INTDIR)\DataFlow.obj"
	-@erase "$(INTDIR)\DataFlow.sbr"
	-@erase "$(INTDIR)\DlgComConfig.obj"
	-@erase "$(INTDIR)\DlgComConfig.sbr"
	-@erase "$(INTDIR)\DlgComData.obj"
	-@erase "$(INTDIR)\DlgComData.sbr"
	-@erase "$(INTDIR)\DlgLogin.obj"
	-@erase "$(INTDIR)\DlgLogin.sbr"
	-@erase "$(INTDIR)\GfxGroupEdit.obj"
	-@erase "$(INTDIR)\GfxGroupEdit.sbr"
	-@erase "$(INTDIR)\GfxOutBarCtrl.obj"
	-@erase "$(INTDIR)\GfxOutBarCtrl.sbr"
	-@erase "$(INTDIR)\GfxPopupMenu.obj"
	-@erase "$(INTDIR)\GfxPopupMenu.sbr"
	-@erase "$(INTDIR)\GpsServer.obj"
	-@erase "$(INTDIR)\GpsServer.pch"
	-@erase "$(INTDIR)\GpsServer.res"
	-@erase "$(INTDIR)\GpsServer.sbr"
	-@erase "$(INTDIR)\GpsServerDoc.obj"
	-@erase "$(INTDIR)\GpsServerDoc.sbr"
	-@erase "$(INTDIR)\GpsServerView.obj"
	-@erase "$(INTDIR)\GpsServerView.sbr"
	-@erase "$(INTDIR)\hyperlink.obj"
	-@erase "$(INTDIR)\hyperlink.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\NEMA0183Parse.obj"
	-@erase "$(INTDIR)\NEMA0183Parse.sbr"
	-@erase "$(INTDIR)\NEMA0183Sentence.obj"
	-@erase "$(INTDIR)\NEMA0183Sentence.sbr"
	-@erase "$(INTDIR)\NEMAGPGGA.obj"
	-@erase "$(INTDIR)\NEMAGPGGA.sbr"
	-@erase "$(INTDIR)\PUBLIC.OBJ"
	-@erase "$(INTDIR)\PUBLIC.SBR"
	-@erase "$(INTDIR)\RSComConfig.obj"
	-@erase "$(INTDIR)\RSComConfig.sbr"
	-@erase "$(INTDIR)\RSOper.obj"
	-@erase "$(INTDIR)\RSOper.sbr"
	-@erase "$(INTDIR)\RSOperType.obj"
	-@erase "$(INTDIR)\RSOperType.sbr"
	-@erase "$(INTDIR)\RSUser.obj"
	-@erase "$(INTDIR)\RSUser.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\SUBCLASS.OBJ"
	-@erase "$(INTDIR)\SUBCLASS.SBR"
	-@erase "$(INTDIR)\ThreadCom.obj"
	-@erase "$(INTDIR)\ThreadCom.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\ViewLog.obj"
	-@erase "$(INTDIR)\ViewLog.sbr"
	-@erase "$(INTDIR)\ViewNEMADecode.obj"
	-@erase "$(INTDIR)\ViewNEMADecode.sbr"
	-@erase "$(INTDIR)\ViewRecvContent.obj"
	-@erase "$(INTDIR)\ViewRecvContent.sbr"
	-@erase "$(INTDIR)\ViewSend.obj"
	-@erase "$(INTDIR)\ViewSend.sbr"
	-@erase "$(INTDIR)\ViewTreeCom.obj"
	-@erase "$(INTDIR)\ViewTreeCom.sbr"
	-@erase "$(OUTDIR)\GpsServer.bsc"
	-@erase "$(OUTDIR)\GpsServer.exe"
	-@erase "$(OUTDIR)\GpsServer.ilk"
	-@erase "$(OUTDIR)\GpsServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\GpsServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\GpsServer.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GpsServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CJButton.sbr" \
	"$(INTDIR)\CJComboBox.sbr" \
	"$(INTDIR)\CJControlBar.sbr" \
	"$(INTDIR)\CJDockBar.sbr" \
	"$(INTDIR)\CJFrameWnd.sbr" \
	"$(INTDIR)\CJMDIFrameWnd.sbr" \
	"$(INTDIR)\CJOutlookBar.sbr" \
	"$(INTDIR)\CJPagerCtrl.sbr" \
	"$(INTDIR)\CJTabctrlBar.sbr" \
	"$(INTDIR)\CJToolBar.sbr" \
	"$(INTDIR)\CoolBar.sbr" \
	"$(INTDIR)\COOLMENU.SBR" \
	"$(INTDIR)\GfxGroupEdit.sbr" \
	"$(INTDIR)\GfxOutBarCtrl.sbr" \
	"$(INTDIR)\GfxPopupMenu.sbr" \
	"$(INTDIR)\hyperlink.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\SUBCLASS.SBR" \
	"$(INTDIR)\RSComConfig.sbr" \
	"$(INTDIR)\RSOper.sbr" \
	"$(INTDIR)\RSOperType.sbr" \
	"$(INTDIR)\RSUser.sbr" \
	"$(INTDIR)\DlgComConfig.sbr" \
	"$(INTDIR)\DlgComData.sbr" \
	"$(INTDIR)\DlgLogin.sbr" \
	"$(INTDIR)\ViewLog.sbr" \
	"$(INTDIR)\ViewNEMADecode.sbr" \
	"$(INTDIR)\ViewRecvContent.sbr" \
	"$(INTDIR)\ViewSend.sbr" \
	"$(INTDIR)\ViewTreeCom.sbr" \
	"$(INTDIR)\ComWorkFlow.sbr" \
	"$(INTDIR)\DataFlow.sbr" \
	"$(INTDIR)\ThreadCom.sbr" \
	"$(INTDIR)\NEMA0183Parse.sbr" \
	"$(INTDIR)\NEMA0183Sentence.sbr" \
	"$(INTDIR)\NEMAGPGGA.sbr" \
	"$(INTDIR)\GpsServer.sbr" \
	"$(INTDIR)\GpsServerDoc.sbr" \
	"$(INTDIR)\GpsServerView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\PUBLIC.SBR" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\GpsServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=winmm.lib mpr.lib version.lib CJ60Lib.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\GpsServer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\GpsServer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CJButton.obj" \
	"$(INTDIR)\CJComboBox.obj" \
	"$(INTDIR)\CJControlBar.obj" \
	"$(INTDIR)\CJDockBar.obj" \
	"$(INTDIR)\CJFrameWnd.obj" \
	"$(INTDIR)\CJMDIFrameWnd.obj" \
	"$(INTDIR)\CJOutlookBar.obj" \
	"$(INTDIR)\CJPagerCtrl.obj" \
	"$(INTDIR)\CJTabctrlBar.obj" \
	"$(INTDIR)\CJToolBar.obj" \
	"$(INTDIR)\CoolBar.obj" \
	"$(INTDIR)\COOLMENU.OBJ" \
	"$(INTDIR)\GfxGroupEdit.obj" \
	"$(INTDIR)\GfxOutBarCtrl.obj" \
	"$(INTDIR)\GfxPopupMenu.obj" \
	"$(INTDIR)\hyperlink.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\SUBCLASS.OBJ" \
	"$(INTDIR)\RSComConfig.obj" \
	"$(INTDIR)\RSOper.obj" \
	"$(INTDIR)\RSOperType.obj" \
	"$(INTDIR)\RSUser.obj" \
	"$(INTDIR)\DlgComConfig.obj" \
	"$(INTDIR)\DlgComData.obj" \
	"$(INTDIR)\DlgLogin.obj" \
	"$(INTDIR)\ViewLog.obj" \
	"$(INTDIR)\ViewNEMADecode.obj" \
	"$(INTDIR)\ViewRecvContent.obj" \
	"$(INTDIR)\ViewSend.obj" \
	"$(INTDIR)\ViewTreeCom.obj" \
	"$(INTDIR)\ComWorkFlow.obj" \
	"$(INTDIR)\DataFlow.obj" \
	"$(INTDIR)\ThreadCom.obj" \
	"$(INTDIR)\NEMA0183Parse.obj" \
	"$(INTDIR)\NEMA0183Sentence.obj" \
	"$(INTDIR)\NEMAGPGGA.obj" \
	"$(INTDIR)\GpsServer.obj" \
	"$(INTDIR)\GpsServerDoc.obj" \
	"$(INTDIR)\GpsServerView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PUBLIC.OBJ" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\GpsServer.res"

"$(OUTDIR)\GpsServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("GpsServer.dep")
!INCLUDE "GpsServer.dep"
!ELSE 
!MESSAGE Warning: cannot find "GpsServer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "GpsServer - Win32 Release" || "$(CFG)" == "GpsServer - Win32 Debug"
SOURCE=.\CJButton.cpp

"$(INTDIR)\CJButton.obj"	"$(INTDIR)\CJButton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJComboBox.cpp

"$(INTDIR)\CJComboBox.obj"	"$(INTDIR)\CJComboBox.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJControlBar.cpp

"$(INTDIR)\CJControlBar.obj"	"$(INTDIR)\CJControlBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJDockBar.cpp

"$(INTDIR)\CJDockBar.obj"	"$(INTDIR)\CJDockBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJFrameWnd.cpp

"$(INTDIR)\CJFrameWnd.obj"	"$(INTDIR)\CJFrameWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJMDIFrameWnd.cpp

"$(INTDIR)\CJMDIFrameWnd.obj"	"$(INTDIR)\CJMDIFrameWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJOutlookBar.cpp

"$(INTDIR)\CJOutlookBar.obj"	"$(INTDIR)\CJOutlookBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJPagerCtrl.cpp

"$(INTDIR)\CJPagerCtrl.obj"	"$(INTDIR)\CJPagerCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJTabctrlBar.cpp

"$(INTDIR)\CJTabctrlBar.obj"	"$(INTDIR)\CJTabctrlBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CJToolBar.cpp

"$(INTDIR)\CJToolBar.obj"	"$(INTDIR)\CJToolBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\CoolBar.cpp

"$(INTDIR)\CoolBar.obj"	"$(INTDIR)\CoolBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\COOLMENU.CPP

"$(INTDIR)\COOLMENU.OBJ"	"$(INTDIR)\COOLMENU.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\GfxGroupEdit.cpp

"$(INTDIR)\GfxGroupEdit.obj"	"$(INTDIR)\GfxGroupEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\GfxOutBarCtrl.cpp

"$(INTDIR)\GfxOutBarCtrl.obj"	"$(INTDIR)\GfxOutBarCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\GfxPopupMenu.cpp

"$(INTDIR)\GfxPopupMenu.obj"	"$(INTDIR)\GfxPopupMenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\hyperlink.cpp

"$(INTDIR)\hyperlink.obj"	"$(INTDIR)\hyperlink.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\Splash.cpp

"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\SUBCLASS.CPP

"$(INTDIR)\SUBCLASS.OBJ"	"$(INTDIR)\SUBCLASS.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\RSComConfig.cpp

"$(INTDIR)\RSComConfig.obj"	"$(INTDIR)\RSComConfig.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\RSOper.cpp

"$(INTDIR)\RSOper.obj"	"$(INTDIR)\RSOper.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\RSOperType.cpp

"$(INTDIR)\RSOperType.obj"	"$(INTDIR)\RSOperType.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\RSUser.cpp

"$(INTDIR)\RSUser.obj"	"$(INTDIR)\RSUser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\DlgComConfig.cpp

"$(INTDIR)\DlgComConfig.obj"	"$(INTDIR)\DlgComConfig.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\DlgComData.cpp

"$(INTDIR)\DlgComData.obj"	"$(INTDIR)\DlgComData.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\DlgLogin.cpp

"$(INTDIR)\DlgLogin.obj"	"$(INTDIR)\DlgLogin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\ViewLog.cpp

"$(INTDIR)\ViewLog.obj"	"$(INTDIR)\ViewLog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\ViewNEMADecode.cpp

"$(INTDIR)\ViewNEMADecode.obj"	"$(INTDIR)\ViewNEMADecode.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\ViewRecvContent.cpp

"$(INTDIR)\ViewRecvContent.obj"	"$(INTDIR)\ViewRecvContent.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\ViewSend.cpp

"$(INTDIR)\ViewSend.obj"	"$(INTDIR)\ViewSend.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\ViewTreeCom.cpp

"$(INTDIR)\ViewTreeCom.obj"	"$(INTDIR)\ViewTreeCom.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\ComWorkFlow.cpp

"$(INTDIR)\ComWorkFlow.obj"	"$(INTDIR)\ComWorkFlow.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\DataFlow.cpp

"$(INTDIR)\DataFlow.obj"	"$(INTDIR)\DataFlow.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\ThreadCom.cpp

"$(INTDIR)\ThreadCom.obj"	"$(INTDIR)\ThreadCom.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\NEMA0183Parse.cpp

"$(INTDIR)\NEMA0183Parse.obj"	"$(INTDIR)\NEMA0183Parse.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\NEMA0183Sentence.cpp

"$(INTDIR)\NEMA0183Sentence.obj"	"$(INTDIR)\NEMA0183Sentence.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\NEMAGPGGA.cpp

"$(INTDIR)\NEMAGPGGA.obj"	"$(INTDIR)\NEMAGPGGA.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\GpsServer.cpp

"$(INTDIR)\GpsServer.obj"	"$(INTDIR)\GpsServer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\GpsServer.rc

"$(INTDIR)\GpsServer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\GpsServerDoc.cpp

"$(INTDIR)\GpsServerDoc.obj"	"$(INTDIR)\GpsServerDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\GpsServerView.cpp

"$(INTDIR)\GpsServerView.obj"	"$(INTDIR)\GpsServerView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\PUBLIC.CPP

"$(INTDIR)\PUBLIC.OBJ"	"$(INTDIR)\PUBLIC.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GpsServer.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "GpsServer - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\GpsServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\GpsServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "GpsServer - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\GpsServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\GpsServer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

