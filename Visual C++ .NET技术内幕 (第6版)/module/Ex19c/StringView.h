// StringView.h : interface of the CStringView class
//


#pragma once

#include "LogScrollView.h"

class CStringView : public CLogScrollView
{
public: // create from serialization only
	CStringView();
	DECLARE_DYNCREATE(CStringView)

// Attributes
public:
	CPoemDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CStringView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
    CRect m_rectPrint;

};

#ifndef _DEBUG  // debug version in StringView.cpp
inline CPoemDoc* CStringView::GetDocument() const
   { return reinterpret_cast<CPoemDoc*>(m_pDocument); }
#endif

