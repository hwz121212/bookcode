// MySplitterView.h : interface of the CMySplitterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSPLITTERVIEW_H__ABADB26D_1120_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYSPLITTERVIEW_H__ABADB26D_1120_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMySplitterView : public CView
{
protected: // create from serialization only
	CMySplitterView();
	DECLARE_DYNCREATE(CMySplitterView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySplitterView)
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
	virtual ~CMySplitterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMySplitterView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#ifndef _DEBUG  // debug version in MySplitterView.cpp
//inline CMySplitterDoc* CMySplitterView::GetDocument()
//   { return (CMySplitterDoc*)m_pDocument; }
//#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPLITTERVIEW_H__ABADB26D_1120_11D4_876D_00001CD613F0__INCLUDED_)
