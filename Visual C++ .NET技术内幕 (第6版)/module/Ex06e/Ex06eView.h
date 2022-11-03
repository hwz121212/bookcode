// Ex06eView.h : interface of the CEx06eView class
//


#pragma once


class CEx06eView : public CView
{
protected: // create from serialization only
	CEx06eView();
	DECLARE_DYNCREATE(CEx06eView)

// Attributes
public:
	CEx06eDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx06eView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex06eView.cpp
inline CEx06eDoc* CEx06eView::GetDocument() const
   { return reinterpret_cast<CEx06eDoc*>(m_pDocument); }
#endif

