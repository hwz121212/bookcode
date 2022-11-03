// Ex06bView.h : interface of the CEx06bView class
//


#pragma once


class CEx06bView : public CView
{
protected: // create from serialization only
	CEx06bView();
	DECLARE_DYNCREATE(CEx06bView)

// Attributes
public:
	CEx06bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx06bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
    void TraceMetrics(CDC* pDC);

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
};

#ifndef _DEBUG  // debug version in Ex06bView.cpp
inline CEx06bDoc* CEx06bView::GetDocument() const
   { return reinterpret_cast<CEx06bDoc*>(m_pDocument); }
#endif

