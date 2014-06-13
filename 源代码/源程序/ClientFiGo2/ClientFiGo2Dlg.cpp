// ClientFiGo2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientFiGo2.h"
#include "ClientFiGo2Dlg.h"
#include "XXSock.h"
#include "ClientSock.h"
#include "quanju.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MaxNumThread 100


HANDLE hEventM[MaxNumThread];
extern HANDLE hMessRecvM[MaxNumThread];
//
extern int numThreadM;
char fileNameM[40]={0};
DWORD fileSizeM=0;

bool FLAGS = false;
extern CClientSock listenSockM,receiveSockM[MaxNumThread];
int	killThrdM = FALSE;//�Ƿ�ֹͣ�˽���! Ҫɱ���߳�!

//

CClientFiGo2Dlg* pMainDlg;

//
CXXSock* m_sockClient;
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
// CClientFiGo2Dlg dialog

CClientFiGo2Dlg::CClientFiGo2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientFiGo2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientFiGo2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientFiGo2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientFiGo2Dlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientFiGo2Dlg, CDialog)
	//{{AFX_MSG_MAP(CClientFiGo2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNGOOD, OnBtnGood)
	ON_BN_CLICKED(IDC_BTNCONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTNRECV, OnBtnRecv)
	ON_BN_CLICKED(IDC_BTNSTOPRECV, OnBtnStoprecv)
	ON_BN_CLICKED(IDC_BTNCLOSE, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientFiGo2Dlg message handlers

BOOL CClientFiGo2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	pMainDlg = this;

	m_sockClient = new CXXSock;
	if ( !m_sockClient->Create(1315, SOCK_DGRAM) )
	{
		delete m_sockClient;
		m_sockClient = NULL;
		MessageBox("UDP-Socket����ʧ�ܣ�");
	}
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	GetDlgItem(IDC_IPADDRESS1)->SetWindowText("127.0.0.1");

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	GetDlgItem(IDC_BTNCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNRECV)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNSTOPRECV)->EnableWindow(FALSE);
	
	// TODO: Add extra initialization here
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientFiGo2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientFiGo2Dlg::OnPaint() 
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
HCURSOR CClientFiGo2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientFiGo2Dlg::OnBtnGood() 
{
	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(m_strIP);
	// TODO: Add your control notification handler code here
	if ( m_sockClient->SendTo( "&*&", 4, 1314, m_strIP ) == SOCKET_ERROR )// ���ַ����� ��Ҫ�߳�����
	{
		MessageBox( GetError(GetLastError()) );
	}
	else
		GetDlgItem(IDC_BTNCONNECT)->EnableWindow(TRUE);
}

void CClientFiGo2Dlg::OnBtnConnect() 
{
	// TODO: Add your control notification handler code here
	CString  strServerIP;
	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(strServerIP);
	for ( int i=0; i<numThreadM; i++ )
	{
		CString str;
		str.Format("%d Connect False!", i);
		receiveSockM[i].Create();
		receiveSockM[i].Connect(strServerIP,7000);
	}
	FLAGS = true;
	GetDlgItem(IDC_BTNRECV)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTNSTOPRECV)->EnableWindow(TRUE);
}

void CClientFiGo2Dlg::OnBtnRecv() 
{
	CFileDialog fileSave( FALSE, NULL, fileNameM );
	if ( IDOK == fileSave.DoModal() )
	{
		m_savePath = fileSave.GetPathName();
	}

	GetDlgItem(IDC_EDITPATH)->SetWindowText(m_savePath);

	m_sockClient->SendTo ("&@&", 4, 1314, m_strIP); // ��֪������ ͬ������ļ���
	// TODO: Add your control notification handler code here
	for ( int i=0; i<numThreadM; i++ )
	{
		if ( (hEventM[i]=CreateEvent(NULL,false,false,NULL)) == NULL )
			AfxMessageBox("Create hE-Event Handle Fail");
		if ( (hMessRecvM[i]=CreateEvent(NULL,false,false,NULL)) == NULL )
			AfxMessageBox("Create hE-Event Handle Fail");
		ResetEvent( hEventM[i] );
		ResetEvent( hMessRecvM[i] );
	}
	_beginthread( RecvNotifyFuncM, 0, NULL );
	for (int i=0; i<numThreadM; i++)
		_beginthread( RecvThreadFuncM, 0, (void *)i );
	if ( FLAGS )
	    AfxMessageBox("RECEICE SUCCESS");
	else
		AfxMessageBox("RECEICE FAIL");
}


CString CClientFiGo2Dlg::GetError(DWORD error)
{
	CString strError;
	switch(error)
	{
	case WSANOTINITIALISED:
		strError="��ʼ������";
		break;
	case WSAENOTCONN:
		strError="�Է�û������";
		break;
	case WSAEWOULDBLOCK :
		strError="�Է��Ѿ��ر�";
		break;
//	case WSAECONNRSED:
//		strError="���ӵĳ��Ա��ܾ�";
//		break;
	case WSAENOTSOCK:
		strError="��һ�����׽����ϳ�����һ������";
		break;
	case WSAEADDRINUSE:
		strError="�ض��ĵ�ַ����ʹ����";
		break;
	case WSAECONNRESET:
		strError="�����������ӱ��ر�";
		break;
	default:
		strError="һ���Դ���";	
	}
	return strError;
}

void CClientFiGo2Dlg::OnBtnStoprecv() 
{
	// TODO: Add your control notification handler code here
	killThrdM = TRUE;
	m_sockClient->SendTo("&S&", 4, 1314, m_strIP);
}

void CClientFiGo2Dlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	::PostMessage( m_hWnd, WM_QUIT, NULL, NULL );
}
