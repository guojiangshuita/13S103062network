#if !defined(AFX_XXSOCK_H__D45146AF_0433_45A2_B0E9_B435C21B3ED4__INCLUDED_)
#define AFX_XXSOCK_H__D45146AF_0433_45A2_B0E9_B435C21B3ED4__INCLUDED_

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
	CString m_strFileName;
	DWORD m_fileSize;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXXSock)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CXXSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XXSOCK_H__D45146AF_0433_45A2_B0E9_B435C21B3ED4__INCLUDED_)
