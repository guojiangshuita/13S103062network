// XXSock.cpp : implementation file
//

#include "stdafx.h"
#include "ClientFiGo2.h"
#include "ClientFiGo2Dlg.h"
#include "XXSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern char fileNameM[40];
extern DWORD fileSizeM;
extern CClientFiGo2Dlg* pMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CXXSock

CXXSock::CXXSock()
{
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
int numThreadM=0;
void CXXSock::OnReceive(int nErrorCode) 
{
	int len = sizeof(SOCKADDR);
	SOCKADDR sock;
	char ch[50]={0};
	// TODO: Add your specialized code here and/or call the base class
	ReceiveFrom( ch, 50, &sock, &len );
//	AfxMessageBox(ch);

	
	if  ( ch[1] == 'T' )//线程数传送
	{
		char num[4] = {0};
		num[0] = ch[3]; //线程数必须是小于100
		num[1] = ch[4];	

		numThreadM = atoi(num);
		CString str;
		str.Format( "服务器启动线程: %d 个", numThreadM );
		AfxMessageBox( str );
	}
	else if ( ch[1] == '$' ) //文件属性内容
	{
		CString strFileMess(ch);
		int start, end;
		start = strFileMess.Find('&', 1);
		end = strFileMess.Find('#');
		CString str;
		str = strFileMess.Mid(start+1, end-start-1);//得到文件大小！
		m_fileSize = atoi((LPCTSTR)str);
		//
		start = end;
		end = strFileMess.GetLength()-2;
		m_strFileName = strFileMess.Mid(start+1, end-start);

//		AfxMessageBox("K"+str+"--"+m_strFileName);

		strcpy(fileNameM, (LPCTSTR)m_strFileName);
		fileSizeM = m_fileSize;
		//文家属性显示
		CString strTemp;
		strTemp.Format( "%ld (B)", fileSizeM );
		(pMainDlg->GetDlgItem(IDC_STASIZE))->SetWindowText(strTemp);
		(pMainDlg->GetDlgItem(IDC_EDITFILENAME))->SetWindowText(fileNameM);
		//进度条
		pMainDlg->m_ctrlProgress.SetRange32( 0, fileSizeM );
		pMainDlg->m_ctrlProgress.SetPos(0);
	}
	
	CAsyncSocket::OnReceive( nErrorCode );
}





















