; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFullScreenDlgDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FullScreenDlgDemo.h"

ClassCount=4
Class1=CFullScreenDlgDemoApp
Class2=CFullScreenDlgDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FullScreenDlgDemo_DIALOG

[CLS:CFullScreenDlgDemoApp]
Type=0
HeaderFile=FullScreenDlgDemo.h
ImplementationFile=FullScreenDlgDemo.cpp
Filter=N

[CLS:CFullScreenDlgDemoDlg]
Type=0
HeaderFile=FullScreenDlgDemoDlg.h
ImplementationFile=FullScreenDlgDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=FullScreenDlgDemoDlg.h
ImplementationFile=FullScreenDlgDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FullScreenDlgDemo_DIALOG]
Type=1
Class=CFullScreenDlgDemoDlg
ControlCount=3
Control1=ID_GOTOFULLSCREEN,button,1342242816
Control2=ID_EXIT,button,1342242816
Control3=IDC_STATIC,static,1342308352

