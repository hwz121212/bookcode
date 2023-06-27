; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx22bView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex22b.h"
LastPage=0

ClassCount=7
Class1=CEx22bApp
Class2=CEx22bDoc
Class3=CEx22bView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_EX22C
Class5=CAboutDlg
Class6=CTest22cDialog
Resource3=IDD_ABOUTBOX
Class7=CTest22dDialog
Resource4=IDD_EX22D

[CLS:CEx22bApp]
Type=0
HeaderFile=ex22b.h
ImplementationFile=ex22b.cpp
Filter=N

[CLS:CEx22bDoc]
Type=0
HeaderFile=ex22bDoc.h
ImplementationFile=ex22bDoc.cpp
Filter=N

[CLS:CEx22bView]
Type=0
HeaderFile=ex22bView.h
ImplementationFile=ex22bView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CEx22bView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_TEST_EX22DDLL




[CLS:CAboutDlg]
Type=0
HeaderFile=ex22b.cpp
ImplementationFile=ex22b.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_TEST_EX22CDLL
Command15=ID_TEST_EX22DDLL
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_EX22C]
Type=1
Class=CTest22cDialog
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_INPUT,edit,1350631552
Control3=IDC_COMPUTE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OUTPUT,edit,1350566016
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816

[CLS:CTest22cDialog]
Type=0
HeaderFile=Test22cDialog.h
ImplementationFile=Test22cDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMPUTE

[DLG:IDD_EX22D]
Type=1
Class=CTest22dDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RYG,RYG,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CTest22dDialog]
Type=0
HeaderFile=Test22dDialog.h
ImplementationFile=Test22dDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CTest22dDialog

