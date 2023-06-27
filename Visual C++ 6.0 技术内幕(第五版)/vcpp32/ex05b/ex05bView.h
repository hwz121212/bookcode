// ex05bView.h : interface of the CEx05bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX05BVIEW_H__B6B0A101_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX05BVIEW_H__B6B0A101_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx05bView : public CView
{
protected: // create from serialization only
	CEx05bView();
	DECLARE_DYNCREATE(CEx05bView)

// Attributes
public:
	CEx05bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx05bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx05bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
    void TraceMetrics(CDC* pDC);

// Generated message map functions
protected:
	//{{AFX_MSG(CEx05bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex05bView.cpp
inline CEx05bDoc* CEx05bView::GetDocument()
   { return (CEx05bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX05BVIEW_H__B6B0A101_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
