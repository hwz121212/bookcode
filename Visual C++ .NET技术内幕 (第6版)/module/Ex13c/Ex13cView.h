// Ex13cView.h : interface of the CEx13cView class
//


#pragma once


class CEx13cView : public CView
{
protected: // create from serialization only
	CEx13cView();
	DECLARE_DYNCREATE(CEx13cView)

// Attributes
public:
	CEx13cDoc* GetDocument() const;

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
	virtual ~CEx13cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex13cView.cpp
inline CEx13cDoc* CEx13cView::GetDocument() const
   { return reinterpret_cast<CEx13cDoc*>(m_pDocument); }
#endif

