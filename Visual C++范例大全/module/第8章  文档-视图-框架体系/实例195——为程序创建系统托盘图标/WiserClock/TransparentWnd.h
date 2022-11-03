//********************************************************************************
//* TransparentWindow.h
//*
//* A transparent window class.
//*
//* Based on the idea of Jason Wylie ,Franz Polzer,Luo yun bin
//* e9225140@student.tuwien.ac.at
//* (C) 2002 by 王鹏
//*
//* Write to me:	mailwp@21cn.com
//********************************************************************************

#if !defined(AFX_TRANSPARENTWND_H__INCLUDED_)
#define AFX_TRANSPARENTWND_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif


class CTransparentWnd : public CWnd
{
public:
	CString m_szBmpFile;
	CString m_szNumFile;
	CBitmap m_mapB;

private:

	int m_nNumX;
	int m_nNumY;
	int m_nSecond;  //前一次扫描时间：秒

	int m_nh1,m_nh2,m_nm1,m_nm2,m_ns1,m_ns2;

public:
	CTransparentWnd();

	void CreateTransparent(LPCTSTR pTitle);
	void SetupRegion(CDC *pDC);
	void FindBmpFile(CString strPath);
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransparentWnd();

protected:
	unsigned short m_BitmapID;

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentWnd)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMinIcon();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnLiben(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
