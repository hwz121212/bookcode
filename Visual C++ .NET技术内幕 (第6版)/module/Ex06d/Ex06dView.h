// Ex06dView.h : interface of the CEx06dView class
//


#pragma once
#include "cdib.h"


class CEx06dView : public CScrollView
{
protected: // create from serialization only
	CEx06dView();
	DECLARE_DYNCREATE(CEx06dView)

// Attributes
public:
	CEx06dDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEx06dView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	CDib m_dibFile;
	CDib m_dibResource;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Ex06dView.cpp
inline CEx06dDoc* CEx06dView::GetDocument() const
   { return reinterpret_cast<CEx06dDoc*>(m_pDocument); }
#endif

