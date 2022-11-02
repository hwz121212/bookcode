/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 管道编程－本地CMD.

  Project: ntLocalCmd.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////
// CmdView.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDVIEW_H__10EC4EE4_E283_11D2_9B23_004005649FB5__INCLUDED_)
#define AFX_CMDVIEW_H__10EC4EE4_E283_11D2_9B23_004005649FB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCmdView view

class CCmdView : public CEditView
{
protected:
	CCmdView();		   // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCmdView)

private:
	HANDLE m_hChildStdinRd, m_hChildStdinWr, 
		m_hChildStdoutRd, m_hChildStdoutWr;
	CWinThread*	m_pReadThread;
	DWORD m_dwProcessId;

	LOGFONT m_lf;
	CFont m_defFont;

	CStringArray m_History;
	int m_nHistoryCounter;
// Attributes
public:

// Operations
public:
	void GetUserInput(CString& input);
	void AddTexts(LPCTSTR string, BOOL bReplace = FALSE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdView)
	protected:
	virtual void OnDraw(CDC* pDC);	  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCmdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif 

	// Generated message map functions
protected:
	BOOL CreateShellRedirect();
	//{{AFX_MSG(CCmdView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditPaste();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddTexts(TCHAR ch);
	void WriteToPipe(LPCTSTR line);
	BOOL CreateChildProcess();

	static UINT ReadPipeThreadProc(LPVOID pParam);
private:
	int GetSelLength();
	int GetCurrentPosition();
	void MoveToEnd();
	void MoveToPrompt();
	int m_nLength;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDVIEW_H__10EC4EE4_E283_11D2_9B23_004005649FB5__INCLUDED_)
