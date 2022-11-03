// Ex20bView.h : interface of the CEx20bView class
//


#pragma once


class CEx20bView : public CView
{
protected: // create from serialization only
	CEx20bView();
	DECLARE_DYNCREATE(CEx20bView)

// Attributes
public:
	CEx20bDoc* GetDocument() const;

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
	virtual ~CEx20bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestEx20cdll();
	afx_msg void OnTestEx20ddll();
};

#ifndef _DEBUG  // debug version in Ex20bView.cpp
inline CEx20bDoc* CEx20bView::GetDocument() const
   { return reinterpret_cast<CEx20bDoc*>(m_pDocument); }
#endif

