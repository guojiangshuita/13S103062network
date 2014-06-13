//StaticMethods

#include "StdAfx.h"
#include "process.h"

#define MaxThread 100
//
extern CString filename;
extern char fileNameM[40];
extern CServerSock listenSocket,sendSockets[MaxThread];
extern int numThread;
extern CServFigoDlg* pMainDlg;
extern CXXSock* m_sockServ;
HANDLE hMessageSend[MaxThread];

//
void SendThreadM(int idx);
//
void GetBeginPosM//get start pos and size of file block
(int TotalThreads,//
 int ThreadIndex,//index of thread (from 1)
 long file_length,//
 long &BgPos,//offset pos from head of file
 long &BlkSize);//size of file block)
//
void SendThreadFuncM(void * pParam);


//
void GetBeginPosM(int TotalThreads,int ThreadIndex, long file_length, long &BgPos, long &BlkSize)
{
	long BlockSize,lastBlockSize,BeginPos;
	//int i;
	BlockSize=file_length/TotalThreads;
	lastBlockSize=file_length;
	BeginPos=0;
	for(int i=1;i<=ThreadIndex-1;i++)
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

void SendThreadFuncM(void * pParam)
{
	int idx=(int)pParam;
	SendThreadM(idx+1);//start from 1
	_endthread();
}

//#define ReadSize 500
static const int ReadSize=500;
void SendThreadM(int idx)
{

	pMainDlg->m_ctrlProgress;

	CFile file;
	char data[ReadSize];
	long BeginPos,Size;
	long FileLength;
	long ReadOnce,LeftToRead,count;
	if ( !file.Open(fileNameM,CFile::modeRead|CFile::shareDenyNone) )
	{
		AfxMessageBox("Read file error");
		return;
	}
	FileLength=(long)file.GetLength();

	sendSockets[idx-1].Send(&FileLength,4);
	WaitForSingleObject(hMessageSend[idx-1],2000);
	sendSockets[idx-1].Send(fileNameM,40);

	GetBeginPosM(numThread,idx,FileLength,BeginPos,Size);
	file.Seek(BeginPos,CFile::begin);
	LeftToRead=Size;

	static DWORD sendCount=0;

	while(LeftToRead>0)
	{
		if ( m_sockServ->m_stopRecved )
		{
			return;
		}

		ReadOnce = ( LeftToRead>ReadSize ? ReadSize : LeftToRead );
		count = file.Read( data,ReadOnce );
		sendCount += ReadOnce;
		WaitForSingleObject( hMessageSend[idx-1],20 );
		while ( SOCKET_ERROR == sendSockets[idx-1].Send(data,count) )
		{
		}
		LeftToRead=LeftToRead-count;

		// set progress Ctrl
		pMainDlg->m_ctrlProgress.SetPos(sendCount);
		CString str;
		str.Format("%ld (B)", sendCount);
		pMainDlg->GetDlgItem(IDC_STACOPYED)->SetWindowText(str);
	}
	file.Close();

	if ( sendCount >= pMainDlg->m_fileSize )
	{
		AfxMessageBox("·¢ËÍÍê±Ï!");
		pMainDlg->m_ctrlProgress.SetPos(0);
	}

}
