// Ex05cView.h : interface of the CEx05cView class
//


#pragma once


class CEx05cView : public CScrollView
{
protected: // create from serialization only
	CEx05cView();
	DECLARE_DYNCREATE(CEx05cView)

// Attributes
public:
	CEx05cDoc* GetDocument() const;

private:
    CRect m_rectEllipse;
    int m_nColor;
	CPoint m_Point;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CEx05cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Ex05cView.cpp
inline CEx05cDoc* CEx05cView::GetDocument() const
   { return reinterpret_cast<CEx05cDoc*>(m_pDocument); }
#endif

