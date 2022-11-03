// Ex05bView.h : interface of the CEx05bView class
//


#pragma once


class CEx05bView : public CView
{
protected: // create from serialization only
	CEx05bView();
	DECLARE_DYNCREATE(CEx05bView)

// Attributes
public:
	CEx05bDoc* GetDocument() const;

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
	virtual ~CEx05bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
    	int m_nColor;
   	CRect m_rectEllipse;

public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
};

#ifndef _DEBUG  // debug version in Ex05bView.cpp
inline CEx05bDoc* CEx05bView::GetDocument() const
   { return reinterpret_cast<CEx05bDoc*>(m_pDocument); }
#endif

