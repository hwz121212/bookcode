; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx14aView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex14a.h"
LastPage=0

ClassCount=5
Class1=CEx14aApp
Class2=CEx14aDoc
Class3=CEx14aView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CEx14aApp]
Type=0
HeaderFile=ex14a.h
ImplementationFile=ex14a.cpp
Filter=N

[CLS:CEx14aDoc]
Type=0
HeaderFile=ex14aDoc.h
ImplementationFile=ex14aDoc.cpp
Filter=N

[CLS:CEx14aView]
Type=0
HeaderFile=ex14aView.h
ImplementationFile=ex14aView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_DRAW_SQUARE

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_DRAW_CIRCLE




[CLS:CAboutDlg]
Type=0
HeaderFile=ex14a.cpp
ImplementationFile=ex14a.cpp
Filter=D

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
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_DRAW_CIRCLE
Command8=ID_DRAW_SQUARE
Command9=ID_DRAW_PATTERN
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_DRAW_SQUARE
Command5=ID_DRAW_CIRCLE
Command6=ID_DRAW_PATTERN
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

