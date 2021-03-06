// RootDlg.cpp : implementation of the CBadRootDlg class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1997-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "httpsvr.h"
#include "RootDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBadRootDlg dialog


CBadRootDlg::CBadRootDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBadRootDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBadRootDlg)
	m_strRoot = _T("");
	//}}AFX_DATA_INIT
}


void CBadRootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBadRootDlg)
	DDX_Text(pDX, IDC_ROOTDIR, m_strRoot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBadRootDlg, CDialog)
	//{{AFX_MSG_MAP(CBadRootDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBadRootDlg message handlers
