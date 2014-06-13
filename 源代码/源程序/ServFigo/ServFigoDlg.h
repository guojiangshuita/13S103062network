// ServFigoDlg.h : header file
//

#if !defined(AFX_SERVFIGODLG_H__92F59E2D_65C8_45FB_92BF_4DFD91D4542D__INCLUDED_)
#define AFX_SERVFIGODLG_H__92F59E2D_65C8_45FB_92BF_4DFD91D4542D__INCLUDED_

#include "ServerSock.h"
#include "XXSock.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServFigoDlg dialog

class CServFigoDlg : public CDialog
{
// Construction
public:
	DWORD m_fileSize;
	void reSetAllOnFile();
	void sendFile();
	static DWORD WINAPI threadPro(LPVOID param);   
	void sendThreadNum();
	void setSth();
	CServFigoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServFigoDlg)
	enum { IDD = IDD_SERVFIGO_DIALOG };
	CProgressCtrl	m_ctrlProgress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServFigoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServFigoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStart();
	afx_msg void OnSelchangeComboThrdtype();
	afx_msg void OnBtnFile();
	afx_msg void OnBtnSend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnExit();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_bitmap;
	
	
	int m_numThread;
	BOOL m_isSingleThread;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVFIGODLG_H__92F59E2D_65C8_45FB_92BF_4DFD91D4542D__INCLUDED_)
