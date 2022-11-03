// BarProgressView.h : interface of the CBarProgressView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BARPROGRESSVIEW_H__3799DEAE_4071_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_BARPROGRESSVIEW_H__3799DEAE_4071_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBarProgressView : public CView
{
protected: // create from serialization only
	CBarProgressView();
	DECLARE_DYNCREATE(CBarProgressView)

// Attributes
public:
	CBarProgressDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarProgressView)
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
	virtual ~CBarProgressView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBarProgressView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BarProgressView.cpp
inline CBarProgressDoc* CBarProgressView::GetDocument()
   { return (CBarProgressDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARPROGRESSVIEW_H__3799DEAE_4071_11D4_9E64_00001A012804__INCLUDED_)
