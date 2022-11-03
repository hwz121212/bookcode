// MyHtmlViewView.h : interface of the CMyHtmlViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYHTMLVIEWVIEW_H__38E95EDC_CCB9_11D2_A71D_D9D3A9F7FE66__INCLUDED_)
#define AFX_MYHTMLVIEWVIEW_H__38E95EDC_CCB9_11D2_A71D_D9D3A9F7FE66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyHtmlViewView : public CHtmlView
{
protected: // create from serialization only
	CMyHtmlViewView();
	DECLARE_DYNCREATE(CMyHtmlViewView)

// Attributes
public:
	CMyHtmlViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyHtmlViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyHtmlViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyHtmlViewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyHtmlViewView.cpp
inline CMyHtmlViewDoc* CMyHtmlViewView::GetDocument()
   { return (CMyHtmlViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYHTMLVIEWVIEW_H__38E95EDC_CCB9_11D2_A71D_D9D3A9F7FE66__INCLUDED_)
