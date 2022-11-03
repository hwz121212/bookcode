// Ex11cView.h : interface of the CEx11cView class
//


#pragma once


class CEx11cView : public CView
{
protected: // create from serialization only
	CEx11cView();
	DECLARE_DYNCREATE(CEx11cView)

// Attributes
public:
	CEx11cDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx11cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Ex11cView.cpp
inline CEx11cDoc* CEx11cView::GetDocument() const
   { return reinterpret_cast<CEx11cDoc*>(m_pDocument); }
#endif

