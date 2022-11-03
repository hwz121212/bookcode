#if !defined(AFX_DWND_H__04BA5A0C_2CA3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_DWND_H__04BA5A0C_2CA3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDWnd window
#define RGB_SETSTATE WM_USER+5
#define RGB_GETSTATE WM_USER+6

LRESULT CALLBACK AFX_EXPORT 
			RygWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

class CDWnd : public CWnd
{
	private:
	int m_nState;
	static CRect s_rect;
	static CPoint s_point;
	static CRect s_rColor[3];
	static CBrush s_bColor[4];
// Construction
public:
	CDWnd();

// Attributes
public:
public:
	static BOOL RegisterWndClass(HINSTANCE hInstance);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDWnd();
private:
	void SetMapping(CDC *pDC);
	void UpdateColor(CDC *pDC,int n);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDWnd)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnSetState(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGetState(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWND_H__04BA5A0C_2CA3_11D4_9E64_00001A012804__INCLUDED_)
