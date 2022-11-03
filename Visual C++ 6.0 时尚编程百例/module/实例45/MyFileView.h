// MyFileView.h : interface of the CMyFileView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFILEVIEW_H__5862DF21_DB10_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_MYFILEVIEW_H__5862DF21_DB10_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyFileView : public CView
{
protected: // create from serialization only
	CMyFileView();
	DECLARE_DYNCREATE(CMyFileView)

// Attributes
public:
	CMyFileDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFileView)
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
	virtual ~CMyFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFileView)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFileView.cpp
inline CMyFileDoc* CMyFileView::GetDocument()
   { return (CMyFileDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFILEVIEW_H__5862DF21_DB10_11D2_A71D_B295A824025F__INCLUDED_)
