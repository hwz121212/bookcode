// Ex07bView.h : interface of the CEx07bView class
//


#pragma once


class CEx07bView : public CView
{
protected: // create from serialization only
	CEx07bView();
	DECLARE_DYNCREATE(CEx07bView)

// Attributes
public:
	CEx07bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx07bView();
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

#ifndef _DEBUG  // debug version in Ex07bView.cpp
inline CEx07bDoc* CEx07bView::GetDocument() const
   { return reinterpret_cast<CEx07bDoc*>(m_pDocument); }
#endif

