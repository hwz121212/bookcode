// Ex12aView.h : interface of the CEx12aView class
//


#pragma once
#include "property.h"

class CEx12aView : public CView
{
private:
    CFontSheet m_sh;
    BOOL m_bDefault; // TRUE default format, FALSE selection

public:
    CRichEditCtrl m_rich;

protected: // create from serialization only
	CEx12aView();
	DECLARE_DYNCREATE(CEx12aView)

// Attributes
public:
	CEx12aDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	void Format(CHARFORMAT &cf);

// Implementation
public:
	virtual ~CEx12aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg LRESULT OnUserApply(WPARAM wParam, LPARAM lParam);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTransferGetdatafromdocument();
	afx_msg void OnTransferStoredataindocument();
	afx_msg void OnUpdateTransferStoredataindocument(CCmdUI *pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFormatDefault();
	afx_msg void OnFormatSelection();
	afx_msg void OnUpdateFormatSelection(CCmdUI *pCmdUI);

};

#ifndef _DEBUG  // debug version in Ex12aView.cpp
inline CEx12aDoc* CEx12aView::GetDocument() const
   { return reinterpret_cast<CEx12aDoc*>(m_pDocument); }
#endif

