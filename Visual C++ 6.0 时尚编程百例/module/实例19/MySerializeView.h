// MySerializeView.h : interface of the CMySerializeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSERIALIZEVIEW_H__DFC8F82D_10B2_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYSERIALIZEVIEW_H__DFC8F82D_10B2_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMySerializeView : public CView
{
protected: // create from serialization only
	CMySerializeView();
	DECLARE_DYNCREATE(CMySerializeView)

// Attributes
public:
	CMySerializeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySerializeView)
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
	virtual ~CMySerializeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMySerializeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MySerializeView.cpp
inline CMySerializeDoc* CMySerializeView::GetDocument()
   { return (CMySerializeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERIALIZEVIEW_H__DFC8F82D_10B2_11D4_876D_00001CD613F0__INCLUDED_)
