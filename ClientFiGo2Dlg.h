// ClientFiGo2Dlg.h : header file
//

#if !defined(AFX_CLIENTFIGO2DLG_H__17C1EFCF_E028_40EA_B5FC_E153E48E9FEE__INCLUDED_)
#define AFX_CLIENTFIGO2DLG_H__17C1EFCF_E028_40EA_B5FC_E153E48E9FEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientFiGo2Dlg dialog

class CClientFiGo2Dlg : public CDialog
{
// Construction
public:
	CString m_savePath;
	CString GetError(DWORD);
	CString m_strIP;
	CClientFiGo2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientFiGo2Dlg)
	enum { IDD = IDD_CLIENTFIGO2_DIALOG };
	CProgressCtrl	m_ctrlProgress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientFiGo2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientFiGo2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnGood();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnRecv();
	afx_msg void OnBtnStoprecv();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTFIGO2DLG_H__17C1EFCF_E028_40EA_B5FC_E153E48E9FEE__INCLUDED_)
