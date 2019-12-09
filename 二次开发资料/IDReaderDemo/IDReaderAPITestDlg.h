// IDReaderAPITestDlg.h : header file
//

#if !defined(AFX_IDREADERAPITESTDLG_H__DA9137FA_8D18_4E67_8360_7DE480F8324E__INCLUDED_)
#define AFX_IDREADERAPITESTDLG_H__DA9137FA_8D18_4E67_8360_7DE480F8324E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CIDReaderAPITestDlg dialog

class CIDReaderAPITestDlg : public CDialog
{
// Construction
public:
	CIDReaderAPITestDlg(CWnd* pParent = NULL);	// standard constructor

    HINSTANCE m_hInstMaster;

// Dialog Data
	//{{AFX_DATA(CIDReaderAPITestDlg)
	enum { IDD = IDD_IDREADERAPITEST_DIALOG };
	CEdit	m_edit_8h10d;
	CStatic	m_static_tips;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDReaderAPITestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIDReaderAPITestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConnect();
	afx_msg void OnDestroy();
	afx_msg void OnBTNRead();
	afx_msg void OnBtnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDREADERAPITESTDLG_H__DA9137FA_8D18_4E67_8360_7DE480F8324E__INCLUDED_)
