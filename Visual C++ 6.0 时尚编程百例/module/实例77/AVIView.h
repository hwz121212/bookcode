// AVIView.h : interface of the CAVIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVIVIEW_H__62F221EC_1F4F_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_AVIVIEW_H__62F221EC_1F4F_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAVIView : public CView
{
protected: // create from serialization only
	CAVIView();
	DECLARE_DYNCREATE(CAVIView)

// Attributes
public:
	CAVIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVIView)
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
	HWND m_hwndMCI;
	virtual ~CAVIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAVIView)
	afx_msg void OnAvi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AVIView.cpp
inline CAVIDoc* CAVIView::GetDocument()
   { return (CAVIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIVIEW_H__62F221EC_1F4F_11D4_B0E6_00001A012804__INCLUDED_)
