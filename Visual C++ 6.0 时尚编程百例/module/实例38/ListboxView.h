// ListboxView.h : interface of the CListboxView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTBOXVIEW_H__9859BEC0_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
#define AFX_LISTBOXVIEW_H__9859BEC0_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CListboxView : public CView
{
protected: // create from serialization only
	CListboxView();
	DECLARE_DYNCREATE(CListboxView)

// Attributes
public:
	CListboxDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListboxView)
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
	virtual ~CListboxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListboxView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ListboxView.cpp
inline CListboxDoc* CListboxView::GetDocument()
   { return (CListboxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXVIEW_H__9859BEC0_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
