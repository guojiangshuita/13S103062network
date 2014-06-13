// ServFigo.h : main header file for the SERVFIGO application
//

#if !defined(AFX_SERVFIGO_H__ADCCA246_D380_4A07_9603_3371F6097CD0__INCLUDED_)
#define AFX_SERVFIGO_H__ADCCA246_D380_4A07_9603_3371F6097CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CServFigoApp:
// See ServFigo.cpp for the implementation of this class
//

class CServFigoApp : public CWinApp
{
public:
	CServFigoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServFigoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CServFigoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVFIGO_H__ADCCA246_D380_4A07_9603_3371F6097CD0__INCLUDED_)
