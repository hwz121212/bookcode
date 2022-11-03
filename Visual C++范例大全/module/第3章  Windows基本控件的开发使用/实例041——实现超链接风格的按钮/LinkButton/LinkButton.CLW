; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHyperLinkButton
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LinkButton.h"

ClassCount=4
Class1=CLinkButtonApp
Class2=CLinkButtonDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CHyperLinkButton
Resource3=IDD_LinkButton_DIALOG

[CLS:CLinkButtonApp]
Type=0
HeaderFile=LinkButton.h
ImplementationFile=LinkButton.cpp
Filter=N

[CLS:CLinkButtonDlg]
Type=0
HeaderFile=LinkButtonDlg.h
ImplementationFile=LinkButtonDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EMAIL

[CLS:CAboutDlg]
Type=0
HeaderFile=LinkButtonDlg.h
ImplementationFile=LinkButtonDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LinkButton_DIALOG]
Type=1
Class=CLinkButtonDlg
ControlCount=5
Control1=IDC_EMAIL,button,1342242827
Control2=IDC_HOMEPAGE,button,1342242827
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CHyperLinkButton]
Type=0
HeaderFile=HyperLinkButton.h
ImplementationFile=HyperLinkButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CHyperLinkButton

