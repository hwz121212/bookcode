// Ex08aView.h : interface of the CEx08aView class
//


#pragma once


class CEx08aView : public CView
{
protected: // create from serialization only
	CEx08aView();
	DECLARE_DYNCREATE(CEx08aView)

// Attributes
public:
	CEx08aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx08aView();
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

#ifndef _DEBUG  // debug version in Ex08aView.cpp
inline CEx08aDoc* CEx08aView::GetDocument() const
   { return reinterpret_cast<CEx08aDoc*>(m_pDocument); }
#endif

