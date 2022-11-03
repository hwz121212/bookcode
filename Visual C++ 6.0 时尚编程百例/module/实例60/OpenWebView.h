// OpenWebView.h : interface of the COpenWebView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENWEBVIEW_H__804DDF8D_E1D0_11D2_A71D_89C2F5392855__INCLUDED_)
#define AFX_OPENWEBVIEW_H__804DDF8D_E1D0_11D2_A71D_89C2F5392855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COpenWebView : public CHtmlView
{
protected: // create from serialization only
	COpenWebView();
	DECLARE_DYNCREATE(COpenWebView)

// Attributes
public:
	COpenWebDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenWebView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenWebView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COpenWebView)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OpenWebView.cpp
inline COpenWebDoc* COpenWebView::GetDocument()
   { return (COpenWebDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENWEBVIEW_H__804DDF8D_E1D0_11D2_A71D_89C2F5392855__INCLUDED_)
