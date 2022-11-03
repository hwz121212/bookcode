// Ex09bView.h : interface of the CEx09bView class
//


#pragma once
#include "cwebbrowser2.h"

class CEx09bView : public CView
{
protected: // create from serialization only
	CEx09bView();
	DECLARE_DYNCREATE(CEx09bView)

// Attributes
public:
	CEx09bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CEx09bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
 CWebBrowser2 m_target;
 CWebBrowser2 m_search; 

private:
    static const char s_engineGoogle[];


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
    afx_msg void OnBeforeNavigateExplorer1(LPCTSTR URL,     
        long Flags, LPCTSTR TargetFrameName,                
        VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel);
    afx_msg void OnTitleChangeExplorer2(LPCTSTR Text);
    DECLARE_EVENTSINK_MAP()

};

#ifndef _DEBUG  // debug version in Ex09bView.cpp
inline CEx09bDoc* CEx09bView::GetDocument() const
   { return reinterpret_cast<CEx09bDoc*>(m_pDocument); }
#endif

