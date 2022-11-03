// MyDialogView.h : interface of the CMyDialogView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDIALOGVIEW_H__54665910_114B_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYDIALOGVIEW_H__54665910_114B_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyDialogView : public CView
{
protected: // create from serialization only
	CMyDialogView();
	DECLARE_DYNCREATE(CMyDialogView)

// Attributes
public:
	CMyDialogDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialogView)
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
	virtual ~CMyDialogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyDialogView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyDialogView.cpp
inline CMyDialogDoc* CMyDialogView::GetDocument()
   { return (CMyDialogDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOGVIEW_H__54665910_114B_11D4_876D_00001CD613F0__INCLUDED_)
