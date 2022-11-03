// switchView.h : interface of the CSwitchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWITCHVIEW_H__B21A70FC_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
#define AFX_SWITCHVIEW_H__B21A70FC_7F31_11D2_BE4E_0000216A06C9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSwitchView : public CView
{
protected: // create from serialization only
	CSwitchView();
	DECLARE_DYNCREATE(CSwitchView)

// Attributes
public:
	CSwitchDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchView)
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
	virtual ~CSwitchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in switchView.cpp
inline CSwitchDoc* CSwitchView::GetDocument()
   { return (CSwitchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHVIEW_H__B21A70FC_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
