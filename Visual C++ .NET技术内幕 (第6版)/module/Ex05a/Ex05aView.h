// Ex05aView.h : interface of the CEx05aView class
//


#pragma once


class CEx05aView : public CView
{
protected: // create from serialization only
	CEx05aView();
	DECLARE_DYNCREATE(CEx05aView)

// Attributes
public:
	CEx05aDoc* GetDocument() const;

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
	virtual ~CEx05aView();
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
	CPoint m_Point;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Ex05aView.cpp
inline CEx05aDoc* CEx05aView::GetDocument() const
   { return reinterpret_cast<CEx05aDoc*>(m_pDocument); }
#endif

