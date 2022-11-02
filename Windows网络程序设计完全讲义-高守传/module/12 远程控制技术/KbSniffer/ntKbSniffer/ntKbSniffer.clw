; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNtKbSnifferDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ntKbSniffer.h"

ClassCount=3
Class1=CNtKbSnifferApp
Class2=CNtKbSnifferDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_NTKBSNIFFER_DIALOG

[CLS:CNtKbSnifferApp]
Type=0
HeaderFile=ntKbSniffer.h
ImplementationFile=ntKbSniffer.cpp
Filter=N

[CLS:CNtKbSnifferDlg]
Type=0
HeaderFile=ntKbSnifferDlg.h
ImplementationFile=ntKbSnifferDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_OPEN

[CLS:CAboutDlg]
Type=0
HeaderFile=ntKbSnifferDlg.h
ImplementationFile=ntKbSnifferDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDOK,button,1342373889

[DLG:IDD_NTKBSNIFFER_DIALOG]
Type=1
Class=CNtKbSnifferDlg
ControlCount=2
Control1=IDC_BUTTON_HOOK,button,1342242816
Control2=IDC_BUTTON_EXIT,button,1342242816

