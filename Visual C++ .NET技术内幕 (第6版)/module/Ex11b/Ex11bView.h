// Ex11bView.h : interface of the CEx11bView class
//


#pragma once


class CEx11bView : public CView
{
protected: // create from serialization only
	CEx11bView();
	DECLARE_DYNCREATE(CEx11bView)

// Attributes
public:
	CEx11bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx11bView();
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

#ifndef _DEBUG  // debug version in Ex11bView.cpp
inline CEx11bDoc* CEx11bView::GetDocument() const
   { return reinterpret_cast<CEx11bDoc*>(m_pDocument); }
#endif

