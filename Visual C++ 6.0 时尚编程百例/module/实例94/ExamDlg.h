// ExamDlg.h : header file
//

#if !defined(AFX_EXAMDLG_H__04BA5A15_2CA3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_EXAMDLG_H__04BA5A15_2CA3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExamDlg dialog
extern "C" __declspec(dllimport) void Cmexport();
#define RGB_SETSTATE WM_USER + 5
#define RGB_GETSTATE WM_USER + 6
class CExamDlg : public CDialog
{
// Construction
public:
	CExamDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExamDlg)
	enum { IDD = IDD_EXAM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
private:
	enum { OFF,RED,YELLOW,GREEN} m_nState;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExamDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg void OnClickedRgb();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMDLG_H__04BA5A15_2CA3_11D4_9E64_00001A012804__INCLUDED_)
