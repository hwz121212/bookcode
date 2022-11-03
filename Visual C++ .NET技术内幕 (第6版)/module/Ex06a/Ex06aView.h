// Ex06aView.h : interface of the CEx06aView class
//


#pragma once


class CEx06aView : public CView
{
protected: // create from serialization only
	CEx06aView();
	DECLARE_DYNCREATE(CEx06aView)

// Attributes
public:
	CEx06aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation

private:
    void ShowFont(CDC* pDC, int& nPos, int nPoints);

public:
	virtual ~CEx06aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
};

#ifndef _DEBUG  // debug version in Ex06aView.cpp
inline CEx06aDoc* CEx06aView::GetDocument() const
   { return reinterpret_cast<CEx06aDoc*>(m_pDocument); }
#endif

