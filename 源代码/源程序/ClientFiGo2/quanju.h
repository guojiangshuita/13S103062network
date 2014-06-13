//StaticMethods

#include "StdAfx.h"
#include "process.h"
#define MaxNumThread 100

//
HANDLE hMessRecvM[MaxNumThread];
extern HANDLE hEventM[MaxNumThread];
extern char fileNameM[40];
extern CClientSock listenSockM,receiveSockM[MaxNumThread];
extern int numThreadM;
extern BOOL killThrdM;

//
extern CClientFiGo2Dlg* pMainDlg;
//
void RecvThreadFuncM(void* pParam);

void RecvThreadM(int idx);

void GetBeginPosM
(
 int TotalThreads,
 int ThreadIndex,
 long file_length,
 long &BgPos,
 long &BlkSize);

void RecvNotifyFuncM(void* pParam);

void CombineFilesM();


void GetBeginPosM(int TotalThreads,int ThreadIndex, long file_length, long &BgPos, long &BlkSize)
{
	long BlockSize,lastBlockSize,BeginPos;

	BlockSize=file_length/TotalThreads;
	lastBlockSize=file_length;
	BeginPos=0;
	for (  int i=1; i<=ThreadIndex-1; i++ )
	{
		lastBlockSize=lastBlockSize-BlockSize;
		BeginPos+=BlockSize;
	}
	if(ThreadIndex==TotalThreads)
	{
		BgPos=BeginPos;
		BlkSize=lastBlockSize;
	}
	else
	{
		BgPos=BeginPos;
		BlkSize=BlockSize;
	}
	return;
}
void RecvThreadFuncM(void* pParam)
{
	int idx=(int)pParam;
	RecvThreadM(idx+1);
	_endthread();
}

static const int ReadSize=500;
void RecvThreadM(int idx)
{
	CFile file;
	char data[ReadSize];
	long BeginPos,Size;
	long FileLength;
	long WriteOnce;
	char filename[200];
	sprintf( filename,"tmpsave-%d.data",idx );//write formatted to a string
	
	if(!file.Open(filename,CFile::modeCreate|CFile::modeWrite))
	{
		AfxMessageBox("write file error");
		return;
	}

	WaitForSingleObject( hMessRecvM[idx-1], 2000 );
	while ( SOCKET_ERROR == receiveSockM[idx-1].Receive(&FileLength,4) );
	WaitForSingleObject( hMessRecvM[idx-1], 2000 );
	while ( SOCKET_ERROR == receiveSockM[idx-1].Receive(fileNameM,40) );

//	ResetEvent( hEventM[idx] );
	
	GetBeginPosM( numThreadM, idx, FileLength, BeginPos, Size );
	while ( Size > 0 )
	{
		static DWORD recvCount=0;
		if ( killThrdM )
		{
			static int count=0;
			count++;
			if ( count >=numThreadM )
			{
				CString str;
				str.Format("All Thread killed!", idx);
				AfxMessageBox(str);
			}
			return;
		}

		WaitForSingleObject( hMessRecvM[idx-1], 20 );
		if ( SOCKET_ERROR == (WriteOnce=receiveSockM[idx-1].Receive(data,ReadSize)) )
		{
			ResetEvent(hMessRecvM[idx-1]);
			continue;
		}
		recvCount += WriteOnce;
		Size=Size-WriteOnce;
		file.Write(data, WriteOnce);

		//
		CString str;
		str.Format("%ld (B)", recvCount);
		pMainDlg->m_ctrlProgress.SetPos(recvCount);
		(pMainDlg->GetDlgItem(IDC_STACOPYED))->SetWindowText(str);
	}
	file.Close();
	SetEvent(hEventM[idx-1]);
}

void CombineFilesM()
{
	CFile fileDest,fileSour;
	CHAR sourname[500];
	static char data[10000];
	LONG count;
	int idex;

	if ( !fileDest.Open(fileNameM, CFile::modeCreate | CFile::modeWrite) )
	{
		AfxMessageBox("Combine: Make Dest File Error");
		return;
	}

	AfxMessageBox( "ComBine!" );
	for ( idex=0; idex<numThreadM; idex++ )
	{
		wsprintf(sourname,"tmpsave-%d.data",idex+1);
		if ( !fileSour.Open(sourname, CFile::modeRead) )
		{
			AfxMessageBox("Combine: 块文件打开失败!");
			return;
		}
		count=fileSour.Read(data, 10000);
		while ( count>0 )
		{
			fileDest.Write(data, count);
			count=fileSour.Read(data, 10000);
		}
		fileSour.Close();

		if ( !DeleteFile(sourname) )
		{
			AfxMessageBox("Combine: 块文件删除失败!");
			return;
		}
	}

	AfxMessageBox( "接收成功!" );
	pMainDlg->m_ctrlProgress.SetPos(0);
	fileDest.Close();
}



void RecvNotifyFuncM(void* pParam)
{
	if ( MAXIMUM_WAIT_OBJECTS < numThreadM )
		AfxMessageBox("线程量已超过上限!");

	if ( numThreadM > 1 )
		WaitForMultipleObjects( numThreadM, hEventM, true, 30000 );

	CombineFilesM();
	_endthread();
}