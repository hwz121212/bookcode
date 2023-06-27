// ex28cView.h : interface of the CEx28cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28CVIEW_H__1EAAB6F7_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX28CVIEW_H__1EAAB6F7_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEx28cView : public CView
{
protected: // create from serialization only
	CEx28cView();
	DECLARE_DYNCREATE(CEx28cView)

// Attributes
public:
	CEx28cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28cView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex28cView.cpp
inline CEx28cDoc* CEx28cView::GetDocument()
   { return (CEx28cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28CVIEW_H__1EAAB6F7_6011_11D0_848F_00400526305B__INCLUDED_)
