// DrawLineView.h : interface of the CDrawLineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWLINEVIEW_H__B3F9E14C_442A_11D4_8838_0000E8E7DF1A__INCLUDED_)
#define AFX_DRAWLINEVIEW_H__B3F9E14C_442A_11D4_8838_0000E8E7DF1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawLineView : public CView
{
protected: // create from serialization only
	CDrawLineView();
	DECLARE_DYNCREATE(CDrawLineView)

// Attributes
public:
	CDrawLineDoc* GetDocument();

// Operations
public:
private:
	POINT begin[2];
	POINT rise[2];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawLineView)
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
	void BeginDrawLine(CClientDC *pDC);

	UINT LineRand(UINT max);
	COLORREF SetColor(int x,int y);
	virtual ~CDrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawLineView)
	afx_msg void OnDrawline();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DrawLineView.cpp
inline CDrawLineDoc* CDrawLineView::GetDocument()
   { return (CDrawLineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWLINEVIEW_H__B3F9E14C_442A_11D4_8838_0000E8E7DF1A__INCLUDED_)
