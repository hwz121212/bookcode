// Ex13aView.h : interface of the CEx13aView class
//


#pragma once


class CEx13aView : public CView
{
protected: // create from serialization only
	CEx13aView();
	DECLARE_DYNCREATE(CEx13aView)

protected:
    CRect m_rect;
    BOOL  m_bCircle;
    BOOL  m_bPattern;

// Attributes
public:
	CEx13aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx13aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
	afx_msg void OnDrawPattern();
	afx_msg void OnUpdateDrawPattern(CCmdUI *pCmdUI);
	afx_msg void OnDrawSquare();
	afx_msg void OnUpdateDrawSquare(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in Ex13aView.cpp
inline CEx13aDoc* CEx13aView::GetDocument() const
   { return reinterpret_cast<CEx13aDoc*>(m_pDocument); }
#endif

