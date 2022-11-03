// Ex22cView.h : interface of the CEx22cView class
//


#pragma once


class CEx22cView : public CView
{
protected: // create from serialization only
	CEx22cView();
	DECLARE_DYNCREATE(CEx22cView)

// Attributes
public:
	CEx22cDoc* GetDocument() const;

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
	virtual ~CEx22cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestSpaceship();
};

#ifndef _DEBUG  // debug version in Ex22cView.cpp
inline CEx22cDoc* CEx22cView::GetDocument() const
   { return reinterpret_cast<CEx22cDoc*>(m_pDocument); }
#endif

