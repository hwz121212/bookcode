// Ex14aView.h : interface of the CEx14aView class
//


#pragma once


class CEx14aView : public CView
{
protected: // create from serialization only
	CEx14aView();
	DECLARE_DYNCREATE(CEx14aView)

// Attributes
public:
	CEx14aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx14aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex14aView.cpp
inline CEx14aDoc* CEx14aView::GetDocument() const
   { return reinterpret_cast<CEx14aDoc*>(m_pDocument); }
#endif

