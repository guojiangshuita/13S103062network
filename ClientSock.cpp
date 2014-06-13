// ClientSock.cpp : implementation file
//

#include "stdafx.h"
#include "ClientFiGo2.h"
#include "ClientSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MaxNumThread 100

CClientSock listenSockM, receiveSockM[MaxNumThread];
extern HANDLE hEventM[MaxNumThread];
extern HANDLE hMessRecvM[MaxNumThread];
extern char fileNameM[40];
extern int numThreadM;


/////////////////////////////////////////////////////////////////////////////
// CClientSock

CClientSock::CClientSock()
{
}

CClientSock::~CClientSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSock member functions

void CClientSock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	static int File_Socket_Connected=0;
	if ( nErrorCode==0 )
	{
		idx=++File_Socket_Connected;
		this->AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);
		if(File_Socket_Connected==numThreadM)
		{
			File_Socket_Connected=0;
			AfxMessageBox("Connect success");
		}
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
}

void CClientSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	SetEvent(hMessRecvM[idx-1]);
	CAsyncSocket::OnReceive(nErrorCode);
}
