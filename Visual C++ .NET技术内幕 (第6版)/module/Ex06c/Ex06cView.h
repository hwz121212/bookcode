// Ex06cView.h : interface of the CEx06cView class
//


#pragma once


class CEx06cView : public CScrollView
{
protected: // create from serialization only
	CEx06cView();
	DECLARE_DYNCREATE(CEx06cView)

// Attributes
public:
	CEx06cDoc* GetDocument() const;

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
	virtual ~CEx06cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
    const CSize m_sizeEllipse; // logical
    CPoint m_pointTopLeft; // logical, top left of ellipse rectangle
    CSize  m_sizeOffset; // device, from rect top left 
                         //  to capture point
    BOOL   m_bCaptured;


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Ex06cView.cpp
inline CEx06cDoc* CEx06cView::GetDocument() const
   { return reinterpret_cast<CEx06cDoc*>(m_pDocument); }
#endif

