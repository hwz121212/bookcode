; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPPClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PPClient.h"

ClassCount=3
Class1=CPPClientApp
Class2=CPPClientDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PPClient_DIALOG

[CLS:CPPClientApp]
Type=0
HeaderFile=PPClient.h
ImplementationFile=PPClient.cpp
Filter=N

[CLS:CPPClientDlg]
Type=0
HeaderFile=PPClientDlg.h
ImplementationFile=PPClientDlg.cpp
Filter=D
LastObject=IDC_MSG
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=PPClientDlg.h
ImplementationFile=PPClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PPClient_DIALOG]
Type=1
Class=CPPClientDlg
ControlCount=6
Control1=ID_SERVER,SysIPAddress32,1342242816
Control2=IDC_SEND,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDC_MSG,edit,1352732740
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

