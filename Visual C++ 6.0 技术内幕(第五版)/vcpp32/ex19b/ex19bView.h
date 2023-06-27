// ex19bView.h : interface of the CEx19bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX19BVIEW_H__7F377D2F_C491_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX19BVIEW_H__7F377D2F_C491_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx19bView : public CView
{
protected: // create from serialization only
	CEx19bView();
	DECLARE_DYNCREATE(CEx19bView)

// Attributes
public:
	CEx19bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx19bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nPage;
	virtual ~CEx19bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx19bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PrintPageFooter(CDC *pDC);
	void PrintPageHeader(CDC *pDC);
};

#ifndef _DEBUG  // debug version in ex19bView.cpp
inline CEx19bDoc* CEx19bView::GetDocument()
   { return (CEx19bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX19BVIEW_H__7F377D2F_C491_11D1_B30A_0080C7360DC1__INCLUDED_)
