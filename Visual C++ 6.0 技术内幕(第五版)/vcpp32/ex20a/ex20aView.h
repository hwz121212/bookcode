// ex20aView.h : interface of the CEx20aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX20AVIEW_H__806617AF_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX20AVIEW_H__806617AF_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx20aView : public CView
{
protected: // create from serialization only
	CEx20aView();
	DECLARE_DYNCREATE(CEx20aView)

// Attributes
public:
	CEx20aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx20aView)
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
	virtual ~CEx20aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx20aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex20aView.cpp
inline CEx20aDoc* CEx20aView::GetDocument()
   { return (CEx20aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX20AVIEW_H__806617AF_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_)
