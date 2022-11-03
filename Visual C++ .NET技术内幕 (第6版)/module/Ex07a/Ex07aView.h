// Ex07aView.h : interface of the CEx07aView class
//


#pragma once


class CEx07aView : public CView
{
protected: // create from serialization only
	CEx07aView();
	DECLARE_DYNCREATE(CEx07aView)

// Attributes
public:
	CEx07aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx07aView();
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

#ifndef _DEBUG  // debug version in Ex07aView.cpp
inline CEx07aDoc* CEx07aView::GetDocument() const
   { return reinterpret_cast<CEx07aDoc*>(m_pDocument); }
#endif

