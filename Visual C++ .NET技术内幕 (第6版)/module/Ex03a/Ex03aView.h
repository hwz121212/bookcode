// Ex03aView.h : interface of the CEx03aView class
//


#pragma once


class CEx03aView : public CView
{
protected: // create from serialization only
	CEx03aView();
	DECLARE_DYNCREATE(CEx03aView)

// Attributes
public:
	CEx03aDoc* GetDocument() const;

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
	virtual ~CEx03aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex03aView.cpp
inline CEx03aDoc* CEx03aView::GetDocument() const
   { return reinterpret_cast<CEx03aDoc*>(m_pDocument); }
#endif

