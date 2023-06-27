// ex27aView.h : interface of the CEx27aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27AVIEW_H__F7547B2D_F63A_11D1_B30A_D09549C10710__INCLUDED_)
#define AFX_EX27AVIEW_H__F7547B2D_F63A_11D1_B30A_D09549C10710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx27aView : public CView
{
protected: // create from serialization only
	CEx27aView();
	DECLARE_DYNCREATE(CEx27aView)

// Attributes
public:
	CEx27aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27aView)
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
	virtual ~CEx27aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27aView)
	afx_msg void OnStorageRead();
	afx_msg void OnStorageWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex27aView.cpp
inline CEx27aDoc* CEx27aView::GetDocument()
   { return (CEx27aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27AVIEW_H__F7547B2D_F63A_11D1_B30A_D09549C10710__INCLUDED_)
