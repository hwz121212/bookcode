// AcceleratorView.h : interface of the CAcceleratorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCELERATORVIEW_H__72E9986D_B87D_11D2_A71D_CAEB1B5C016B__INCLUDED_)
#define AFX_ACCELERATORVIEW_H__72E9986D_B87D_11D2_A71D_CAEB1B5C016B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const COLORREF BLACK=RGB(0,0,0);
const COLORREF RED=RGB(255,0,0);
const COLORREF GREEN=RGB(0,255,0);
const COLORREF BLUE=RGB(0,0,255);

class CAcceleratorView : public CView
{
protected: // create from serialization only
	CAcceleratorView();
	DECLARE_DYNCREATE(CAcceleratorView)

// Attributes
public:
	CAcceleratorDoc* GetDocument();

// Operations
public:
	COLORREF m_pColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcceleratorView)
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
	virtual ~CAcceleratorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAcceleratorView)
	afx_msg void OnColorBlue();
	afx_msg void OnColorGreen();
	afx_msg void OnColorRed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AcceleratorView.cpp
inline CAcceleratorDoc* CAcceleratorView::GetDocument()
   { return (CAcceleratorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCELERATORVIEW_H__72E9986D_B87D_11D2_A71D_CAEB1B5C016B__INCLUDED_)
