// Ex24aView.h : interface of the CEx24aView class
//


#pragma once


#define WM_VIEWPALETTECHANGED  WM_USER + 5


class CEx24aView : public CScrollView
{
    // for tracking
    CRectTracker m_tracker;
    CRect m_rectTracker; // logical coordinates
    CSize m_sizeTotal;   // document size


protected: // create from serialization only
	CEx24aView();
	DECLARE_DYNCREATE(CEx24aView)

// Attributes
public:
	CEx24aDoc* GetDocument() const;

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
	virtual ~CEx24aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
    afx_msg void OnEditCopyto();
    afx_msg void OnEditPastefrom();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    virtual void OnInitialUpdate();
	afx_msg LRESULT OnViewPaletteChanged(WPARAM wParam, LPARAM lParam);

    BOOL DoPasteDib(COleDataObject* pDataObject);
    COleDataSource* CEx24aView::SaveDib();
};

#ifndef _DEBUG  // debug version in Ex24aView.cpp
inline CEx24aDoc* CEx24aView::GetDocument() const
   { return reinterpret_cast<CEx24aDoc*>(m_pDocument); }
#endif

