; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStudentDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex17a.h"
LastPage=0

ClassCount=5
Class1=CEx17aApp
Class2=CStudentDoc
Class3=CStudentView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_STUDENT
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource7=IDR_MAINFRAME

[CLS:CEx17aApp]
Type=0
HeaderFile=ex17a.h
ImplementationFile=ex17a.cpp
Filter=N

[CLS:CStudentDoc]
Type=0
HeaderFile=StuDoc.h
ImplementationFile=StuDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_FILE_SAVE

[CLS:CStudentView]
Type=0
HeaderFile=StuView.h
ImplementationFile=StuView.cpp
Filter=D
LastObject=CStudentView
BaseClass=CFormView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=ex17a.cpp
ImplementationFile=ex17a.cpp
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

[DLG:IDD_STUDENT]
Type=1
Class=CStudentView
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NAME,edit,1350631552
Control5=IDC_GRADE,edit,1350631552
Control6=IDC_CLEAR,button,1342242816

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

