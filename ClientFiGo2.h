// ClientFiGo2.h : main header file for the CLIENTFIGO2 application
//

#if !defined(AFX_CLIENTFIGO2_H__B7B7CB48_ED9B_41C6_BA10_3ADB870E5015__INCLUDED_)
#define AFX_CLIENTFIGO2_H__B7B7CB48_ED9B_41C6_BA10_3ADB870E5015__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientFiGo2App:
// See ClientFiGo2.cpp for the implementation of this class
//

class CClientFiGo2App : public CWinApp
{
public:
	CClientFiGo2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientFiGo2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientFiGo2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTFIGO2_H__B7B7CB48_ED9B_41C6_BA10_3ADB870E5015__INCLUDED_)
