#if !defined(AFX_XXSOCK_H__A3A3CD98_06F7_4332_B2D1_C93344888FCF__INCLUDED_)
#define AFX_XXSOCK_H__A3A3CD98_06F7_4332_B2D1_C93344888FCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XXSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CXXSock command target

class CXXSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CXXSock();
	virtual ~CXXSock();

// Overrides
public:
	BOOL m_stopRecved;
	BOOL m_sendOK;
	BOOL m_OK;
	SOCKADDR m_saToSend;
	CString m_strRecv;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXXSock)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CXXSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XXSOCK_H__A3A3CD98_06F7_4332_B2D1_C93344888FCF__INCLUDED_)
