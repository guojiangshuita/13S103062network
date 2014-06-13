// XXSock.cpp : implementation file
//

#include "stdafx.h"
#include "ServFigo.h"
#include "XXSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern int numThread;
/////////////////////////////////////////////////////////////////////////////
// CXXSock

CXXSock::CXXSock()
{
	m_strRecv = "";
	m_OK = FALSE;
	m_sendOK = FALSE;
	m_stopRecved = FALSE;
}

CXXSock::~CXXSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CXXSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CXXSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CXXSock member functions

void CXXSock::OnReceive(int nErrorCode) 
{
	int len = sizeof(SOCKADDR);
	char ch[10];
	// TODO: Add your specialized code here and/or call the base class
	ReceiveFrom( ch, 10, &m_saToSend, &len );
	if ( ch[1] == '*' && numThread != 0 )
	{
		m_OK = TRUE;
		char num[10]={0};
		itoa(numThread, num, 10);
		num[4] = num[1];
		num[3] = num[0];
		num[2] = '&';
		num[1] = 'T';
		num[0] = '&';
		SendTo( num, 10, &m_saToSend, sizeof(SOCKADDR) );
	}
	else if ( strcmp(ch,"&@&")==0 )
	{
		m_sendOK = TRUE;
	}
	else if ( strcmp(ch,"&S&")==0 )
	{
		m_stopRecved = TRUE;
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void CXXSock::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
}
