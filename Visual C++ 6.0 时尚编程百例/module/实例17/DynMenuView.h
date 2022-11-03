// DynMenuView.h : interface of the CDynMenuView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNMENUVIEW_H__6ABF34ED_E453_11D2_A71D_A44E1A83F14B__INCLUDED_)
#define AFX_DYNMENUVIEW_H__6ABF34ED_E453_11D2_A71D_A44E1A83F14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDynMenuView : public CView
{
protected: // create from serialization only
	CDynMenuView();
	DECLARE_DYNCREATE(CDynMenuView)

// Attributes
public:
	CDynMenuDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynMenuView)
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
	virtual ~CDynMenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDynMenuView)
	afx_msg void OnExpand();
	afx_msg void OnStandard();
	afx_msg void OnUpdateOptions(CCmdUI* pCmdUI);
	afx_msg void OnBlack();
	afx_msg void OnRed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DynMenuView.cpp
inline CDynMenuDoc* CDynMenuView::GetDocument()
   { return (CDynMenuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNMENUVIEW_H__6ABF34ED_E453_11D2_A71D_A44E1A83F14B__INCLUDED_)
