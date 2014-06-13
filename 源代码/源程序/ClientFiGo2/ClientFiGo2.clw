; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CClientFiGo2Dlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ClientFiGo2.h"

ClassCount=5
Class1=CClientFiGo2App
Class2=CClientFiGo2Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CClientSock
Class4=CXXSock
Resource3=IDD_CLIENTFIGO2_DIALOG

[CLS:CClientFiGo2App]
Type=0
HeaderFile=ClientFiGo2.h
ImplementationFile=ClientFiGo2.cpp
Filter=N

[CLS:CClientFiGo2Dlg]
Type=0
HeaderFile=ClientFiGo2Dlg.h
ImplementationFile=ClientFiGo2Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_PROGRESS1

[CLS:CAboutDlg]
Type=0
HeaderFile=ClientFiGo2Dlg.h
ImplementationFile=ClientFiGo2Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENTFIGO2_DIALOG]
Type=1
Class=CClientFiGo2Dlg
ControlCount=18
Control1=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control2=IDC_BTNGOOD,button,1342242816
Control3=IDC_BTNCONNECT,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BTNRECV,button,1342242816
Control6=IDC_BTNSTOPRECV,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_PROGRESS1,msctls_progress32,1350565888
Control9=IDC_BTNCLOSE,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDITFILENAME,edit,1342244992
Control16=IDC_EDITPATH,edit,1342244992
Control17=IDC_STASIZE,static,1342308352
Control18=IDC_STACOPYED,static,1342308352

[CLS:CXXSock]
Type=0
HeaderFile=XXSock.h
ImplementationFile=XXSock.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

[CLS:CClientSock]
Type=0
HeaderFile=ClientSock.h
ImplementationFile=ClientSock.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

