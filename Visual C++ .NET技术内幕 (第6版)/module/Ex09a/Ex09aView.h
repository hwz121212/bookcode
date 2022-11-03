// Ex09aView.h : interface of the CEx09aView class
//


#pragma once


class CEx09aView : public CView
{
protected: // create from serialization only
	CEx09aView();
	DECLARE_DYNCREATE(CEx09aView)

// Attributes
public:
	CEx09aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx09aView();
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

#ifndef _DEBUG  // debug version in Ex09aView.cpp
inline CEx09aDoc* CEx09aView::GetDocument() const
   { return reinterpret_cast<CEx09aDoc*>(m_pDocument); }
#endif

