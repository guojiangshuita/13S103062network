; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServFigoDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ServFigo.h"

ClassCount=6
Class1=CServFigoApp
Class2=CServFigoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CServerSock
Class6=CXXSock
Class4=CServSock
Resource3=IDD_SERVFIGO_DIALOG

[CLS:CServFigoApp]
Type=0
HeaderFile=ServFigo.h
ImplementationFile=ServFigo.cpp
Filter=N

[CLS:CServFigoDlg]
Type=0
HeaderFile=ServFigoDlg.h
ImplementationFile=ServFigoDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CServFigoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ServFigoDlg.h
ImplementationFile=ServFigoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERVFIGO_DIALOG]
Type=1
Class=CServFigoDlg
ControlCount=19
Control1=IDC_BTNSTART,button,1342242816
Control2=IDC_BTNFILE,button,1342242816
Control3=IDC_COMBOTHRDTYPE,combobox,1344340226
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBOTHRDNUM,combobox,1344339970
Control7=IDC_BTNSEND,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STAFILESIZE,static,1342308352
Control10=IDC_STACOPYED,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDITPATH,edit,1342244992
Control16=IDC_EDITFILENAME,edit,1342244992
Control17=IDC_PROGRESS1,msctls_progress32,1342177281
Control18=IDC_STATIC,static,1342308352
Control19=IDC_BTNEXIT,button,1342242816

[CLS:CServSock]
Type=0
HeaderFile=ServSock.h
ImplementationFile=ServSock.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

[CLS:CServerSock]
Type=0
HeaderFile=ServerSock.h
ImplementationFile=ServerSock.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

[CLS:CXXSock]
Type=0
HeaderFile=XXSock.h
ImplementationFile=XXSock.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

