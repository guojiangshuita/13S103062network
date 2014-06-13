#if !defined(AFX_SERVERSOCK_H__C805CFF7_412A_4CF2_AD04_72A5FB5CC5F8__INCLUDED_)
#define AFX_SERVERSOCK_H__C805CFF7_412A_4CF2_AD04_72A5FB5CC5F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSock command target

class CServerSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CServerSock();
	virtual ~CServerSock();

// Overrides
public:
	static int File_Socket_Accepted;
	int idx;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSock)
	public:
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCK_H__C805CFF7_412A_4CF2_AD04_72A5FB5CC5F8__INCLUDED_)
