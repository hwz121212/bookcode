// ex14cView.h : interface of the CEx14cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX14CVIEW_H__C7C8580D_E3B0_11D1_8524_A6295F36C950__INCLUDED_)
#define AFX_EX14CVIEW_H__C7C8580D_E3B0_11D1_8524_A6295F36C950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx14cView : public CView
{
protected: // create from serialization only
	CEx14cView();
	DECLARE_DYNCREATE(CEx14cView)

// Attributes
public:
	CEx14cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14cView)
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
	virtual ~CEx14cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx14cView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex14cView.cpp
inline CEx14cDoc* CEx14cView::GetDocument()
   { return (CEx14cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14CVIEW_H__C7C8580D_E3B0_11D1_8524_A6295F36C950__INCLUDED_)
