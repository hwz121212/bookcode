// ex35cView.h : interface of the CEx35cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX35CVIEW_H__496552FD_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
#define AFX_EX35CVIEW_H__496552FD_957C_11D0_85C0_97AC5D47DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx35cCntrItem;

class CEx35cView : public CRichEditView
{
protected: // create from serialization only
	CEx35cView();
	DECLARE_DYNCREATE(CEx35cView)

// Attributes
public:
	CEx35cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx35cView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx35cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx35cView)

		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex35cView.cpp
inline CEx35cDoc* CEx35cView::GetDocument()
   { return (CEx35cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX35CVIEW_H__496552FD_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
