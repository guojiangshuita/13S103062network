#if !defined(AFX_CLIENTSOCK_H__6298F303_9BBF_45CA_AB4A_394A5B9930D9__INCLUDED_)
#define AFX_CLIENTSOCK_H__6298F303_9BBF_45CA_AB4A_394A5B9930D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSock command target

class CClientSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CClientSock();
	virtual ~CClientSock();

// Overrides
public:
	int idx;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCK_H__6298F303_9BBF_45CA_AB4A_394A5B9930D9__INCLUDED_)
