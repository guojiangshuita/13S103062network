// ServerSock.cpp : implementation file
//

#include "stdafx.h"
#include "ServFigo.h"
#include "ServerSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MaxThread 100

extern int numThread;
/////////////////////////////////////////////////////////////////////////////
// CServerSock

CServerSock::CServerSock()
{
}

CServerSock::~CServerSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0


CServerSock listenSocket,sendSockets[MaxThread];
extern HANDLE hMessageSend[MaxThread];
BOOL isConnectedM = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CServerSock member functions

void CServerSock::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
}

int CServerSock::File_Socket_Accepted = 0;

void CServerSock::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	// TODO: 在此添加专用代码和/或调用基类
//	static int File_Socket_Accepted=0;
	if ( !listenSocket.Accept(sendSockets[File_Socket_Accepted]) )
	{
		AfxMessageBox("Connect fail");
		return;
	}
	sendSockets[File_Socket_Accepted].AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);
	idx=++File_Socket_Accepted;
	if(File_Socket_Accepted==numThread)
	{
		AfxMessageBox("Connect success");
		isConnectedM = TRUE;
		listenSocket.Close();
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CServerSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	SetEvent(hMessageSend[idx-1]);
	CAsyncSocket::OnSend(nErrorCode);
}
