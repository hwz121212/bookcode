// Font2View.h : interface of the CFont2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONT2VIEW_H__BAE6D160_12FA_11D4_A927_00001A012804__INCLUDED_)
#define AFX_FONT2VIEW_H__BAE6D160_12FA_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFont2View : public CView
{
protected: // create from serialization only
	CFont2View();
	DECLARE_DYNCREATE(CFont2View)

// Attributes
public:
	CFont2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFont2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_dOrientation;
	int m_dEscapement;
	virtual ~CFont2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFont2View)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFont();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Font2View.cpp
inline CFont2Doc* CFont2View::GetDocument()
   { return (CFont2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONT2VIEW_H__BAE6D160_12FA_11D4_A927_00001A012804__INCLUDED_)
