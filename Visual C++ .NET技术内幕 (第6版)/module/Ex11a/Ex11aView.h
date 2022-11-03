// Ex11aView.h : interface of the CEx11aView class
//


#pragma once


class CEx11aView : public CView
{
protected: // create from serialization only
	CEx11aView();
	DECLARE_DYNCREATE(CEx11aView)

// Attributes
public:
	CEx11aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx11aView();
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

#ifndef _DEBUG  // debug version in Ex11aView.cpp
inline CEx11aDoc* CEx11aView::GetDocument() const
   { return reinterpret_cast<CEx11aDoc*>(m_pDocument); }
#endif

