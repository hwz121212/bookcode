; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStudentView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex18a.h"
LastPage=0

ClassCount=6
Class1=CEx18aApp
Class2=CStudentDoc
Class3=CStudentView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_STUDENT
Resource2=IDD_EX18A_FORM
Resource3=IDD_ABOUTBOX
Resource6=IDR_EX18ATYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource7=IDR_MAINFRAME

[CLS:CEx18aApp]
Type=0
HeaderFile=ex18a.h
ImplementationFile=ex18a.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CEx18aApp

[CLS:CStudentDoc]
Type=0
HeaderFile=StuDoc.h
ImplementationFile=StuDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CStudentDoc

[CLS:CStudentView]
Type=0
HeaderFile=StuView.h
ImplementationFile=StuView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=ID_STUDENT_NEXT

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=ex18a.cpp
ImplementationFile=ex18a.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_EX18ATYPE]
Type=1
Class=CStudentView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

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

[DLG:IDD_STUDENT]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NAME,edit,1350631552
Control5=IDC_GRADE,edit,1350631552
Control6=IDC_CLEAR,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_STUDENT_HOME
Command5=ID_STUDENT_PREV
Command6=ID_STUDENT_NEXT
Command7=ID_STUDENT_END
Command8=ID_STUDENT_DEL
Command9=ID_STUDENT_INS
Command10=ID_FILE_PRINT
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_CLEAR_ALL
Command8=ID_STUDENT_HOME
Command9=ID_STUDENT_PREV
Command10=ID_STUDENT_NEXT
Command11=ID_STUDENT_END
Command12=ID_STUDENT_DEL
Command13=ID_STUDENT_INS
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

