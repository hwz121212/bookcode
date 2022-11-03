// Ex07cView.h : interface of the CEx07cView class
//


#pragma once

class CEx07cDialog;

class CEx07cView : public CView
{
protected: // create from serialization only
	CEx07cView();
	DECLARE_DYNCREATE(CEx07cView)

// Attributes
public:
	CEx07cDoc* GetDocument() const;

private:
    CEx07cDialog* m_pDlg;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx07cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg LRESULT OnGoodbye(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // debug version in Ex07cView.cpp
inline CEx07cDoc* CEx07cView::GetDocument() const
   { return reinterpret_cast<CEx07cDoc*>(m_pDocument); }
#endif

