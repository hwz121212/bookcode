// Ex08bView.h : interface of the CEx08bView class
//


#pragma once


class CEx08bView : public CView
{
protected: // create from serialization only
	CEx08bView();
	DECLARE_DYNCREATE(CEx08bView)

// Attributes
public:
	CEx08bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEx08bView();
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

#ifndef _DEBUG  // debug version in Ex08bView.cpp
inline CEx08bDoc* CEx08bView::GetDocument() const
   { return reinterpret_cast<CEx08bDoc*>(m_pDocument); }
#endif

