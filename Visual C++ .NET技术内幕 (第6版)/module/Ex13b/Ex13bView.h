// Ex13bView.h : interface of the CEx13bView class
//


#pragma once


class CEx13bView : public CView
{
protected: // create from serialization only
	CEx13bView();
	DECLARE_DYNCREATE(CEx13bView)

// Attributes
public:
	CEx13bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx13bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Ex13bView.cpp
inline CEx13bDoc* CEx13bView::GetDocument() const
   { return reinterpret_cast<CEx13bDoc*>(m_pDocument); }
#endif

