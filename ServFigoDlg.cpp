// ServFigoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServFigo.h"
#include "ServFigoDlg.h"
#include "quanju.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MaxThread 100
//
extern CServerSock listenSocket,sendSockets[MaxThread];
extern HANDLE hMessageSend[MaxThread];
extern BOOL isConnectedM;

//
CString filename;
char fileNameM[40]={0};

//
CXXSock* m_sockServ;	// for 第一次握手用
int numThread = 0;		// 传线程数
//
CServFigoDlg* pMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServFigoDlg dialog

CServFigoDlg::CServFigoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServFigoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServFigoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_isSingleThread = FALSE;
	m_numThread = 1;
}

void CServFigoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServFigoDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServFigoDlg, CDialog)
	//{{AFX_MSG_MAP(CServFigoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNSTART, OnBtnStart)
	ON_CBN_SELCHANGE(IDC_COMBOTHRDTYPE, OnSelchangeComboThrdtype)
	ON_BN_CLICKED(IDC_BTNFILE, OnBtnFile)
	ON_BN_CLICKED(IDC_BTNSEND, OnBtnSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNEXIT, OnBtnExit)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServFigoDlg message handlers

BOOL CServFigoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	pMainDlg = this;

	m_sockServ = new CXXSock();
	if ( !m_sockServ->Create(1314, SOCK_DGRAM) )
	{
		delete m_sockServ;
		m_sockServ = NULL;
		MessageBox("UDP-Socket创建失败！");
	}

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	m_bitmap.LoadBitmap(IDB_BITMAP1);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->AddString("单线程");
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->AddString("多线程");
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->SetCurSel(0);

	for ( int idex=1; idex<=20; idex++)
	{
		CString str;
		str.Format("%d",idex);
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->EnableWindow(FALSE);

	GetDlgItem(IDC_BTNFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNSEND)->EnableWindow(FALSE);

	GetDlgItem(IDC_STACOPYED)->SetWindowText("0 (B)");
	GetDlgItem(IDC_STAFILESIZE)->SetWindowText("0 (B)");

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	


	HWND hwnd = m_hWnd;
	HANDLE hd = CreateThread(NULL,0,threadPro,(LPVOID)&hwnd,NULL,NULL);
	CloseHandle(hd);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServFigoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServFigoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServFigoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CServFigoDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	setSth();

	listenSocket.Create(7000);
	listenSocket.Listen();

	GetDlgItem(IDC_BTNSTART)->EnableWindow(FALSE);
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->EnableWindow(FALSE);
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->EnableWindow(FALSE);


	MessageBox("服务器已经启动...");

	GetDlgItem(IDC_BTNFILE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTNSEND)->EnableWindow(TRUE);
}


void CServFigoDlg::setSth() //设置线程选框~
{
	CString strSel;
	int index;
	index = ((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->GetLBText( index, strSel );
	if ( strSel == "单线程" )
	{
		m_isSingleThread = TRUE;
		numThread = 1;
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->EnableWindow(FALSE);
	}
	else
	{
		m_isSingleThread = FALSE;
		index = ((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->GetLBText( index, strSel );
		m_numThread = atoi((LPCTSTR)strSel);
		numThread = m_numThread;
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->EnableWindow(TRUE);
	}
}

void CServFigoDlg::sendThreadNum()
{
	
}


DWORD WINAPI CServFigoDlg::threadPro(LPVOID param)
{
	HWND hwnd = *(HWND*)param;
//	BOOL ok = ((CServFigoDlg*)FromHandle(hwnd))->m_sockServ->m_OK;
	BOOL ok = m_sockServ->m_OK;
	while ( ! ok )
	{
		BOOL ok = m_sockServ->m_OK;
	}

	int num = ((CServFigoDlg*)FromHandle(hwnd))->m_numThread;
//	m_sockServ->SendTo( &num, 4, &m_sockServ->m_saToSend, sizeof(SOCKADDR) );

	AfxMessageBox("send ok!");
	return 0;
}

void CServFigoDlg::OnSelchangeComboThrdtype() 
{
	// TODO: Add your control notification handler code here
	CString strSel;
	int index;
	index = ((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBOTHRDTYPE))->GetLBText( index, strSel );
	if ( strSel == "单线程" )
	{
		m_isSingleThread = TRUE;
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->EnableWindow(FALSE);
	}
	else
	{
		m_isSingleThread = FALSE;
		index = ((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->GetLBText( index, strSel );
		m_numThread = atoi((LPCTSTR)strSel);
		numThread = m_numThread;
		((CComboBox*)GetDlgItem(IDC_COMBOTHRDNUM))->EnableWindow(TRUE);
	}
}

void CServFigoDlg::OnBtnFile() 
{
	// TODO: Add your control notification handler code here
//	reSetAllOnFile();

	CFileDialog openFile(TRUE);
	if ( IDOK == openFile.DoModal() )
	{
		filename=openFile.GetFileName();
		strcpy( fileNameM,filename.GetBuffer(0) );
	}
	else return;

	CString strFilePath = openFile.GetPathName();
	CString strFileSize;

	CFile file( fileNameM, CFile::modeRead );
	m_fileSize = file.GetLength();
	//itoa( fileSize, strFileSize.GetBuffer(0), 10 );
	strFileSize.Format("%ld (B)", m_fileSize);
	file.Close();

	GetDlgItem(IDC_EDITFILENAME)->SetWindowText(fileNameM);
	GetDlgItem(IDC_STAFILESIZE)->SetWindowText(strFileSize);
	GetDlgItem(IDC_EDITPATH)->SetWindowText(strFilePath);
	
}

void CServFigoDlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	if ( strcmp(fileNameM,"")==0 )
	{
		MessageBox("请先选取文件!");
		return;
	}

	if ( ! isConnectedM )
	{
		MessageBox("无连接!");
		return;
	}

	CString strFileMess;
	strFileMess.Format("&$&%ld", m_fileSize);
	strFileMess += '#';
	strFileMess += fileNameM;
	strFileMess += '#';
	m_sockServ->SendTo( (LPCTSTR)strFileMess, strFileMess.GetLength(),
			&m_sockServ->m_saToSend, sizeof(SOCKADDR) );
	
	SetTimer( 0, 1000, NULL);
	SetTimer( 1, 1000, NULL);
}

void CServFigoDlg::sendFile()
{
	KillTimer(0);

	m_ctrlProgress.SetRange32(0, m_fileSize);

	for ( int i=0; i<numThread; i++ )
	{
		if((hMessageSend[i]=CreateEvent(NULL,false,false,NULL))==NULL)
			AfxMessageBox("Create hE-Event Handle Fail");
		ResetEvent( hMessageSend[i] );
	}
	for(int i=0;i<numThread;i++)
		_beginthread( SendThreadFuncM, 0, (void *)i );
}

void CServFigoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch ( nIDEvent )
	{
	case 0 :
		if ( m_sockServ->m_sendOK )
			sendFile();
		break;
	case 1 :
		if ( m_sockServ->m_stopRecved )
		{
			KillTimer(1);
			MessageBox("对方已经终止接受! 请退出...");
			
		}
		break;
	default:
		;
	}
	CDialog::OnTimer(nIDEvent);
}

void CServFigoDlg::reSetAllOnFile()
{
	memset(fileNameM,40,'\0');
	m_ctrlProgress.SetPos(0);
	m_fileSize = 0;
	m_sockServ->m_OK = FALSE;
	m_sockServ->m_sendOK = FALSE;
	m_sockServ->m_stopRecved = FALSE;
	m_sockServ->m_strRecv = "";

	GetDlgItem(IDC_STACOPYED)->SetWindowText("0 (B)");

	CServerSock::File_Socket_Accepted = 0;
}

void CServFigoDlg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_QUIT, NULL, NULL);
}

BOOL CServFigoDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default 
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&m_bitmap);
	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);
	
//	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}
