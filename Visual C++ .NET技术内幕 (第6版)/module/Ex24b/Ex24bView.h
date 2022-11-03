// Ex24bView.h : interface of the CEx24bView class
//


#pragma once


class CEx24bView : public CScrollView
{
// for tracking
    CRectTracker m_tracker;
    CRect m_rectTracker;
// for drag-and-drop
    CRect m_rectTrackerEnter; // original logical coords
    COleDropTarget m_dropTarget;
    CSize m_dragOffset; // device coords

    CSize m_sizeTotal;  // document size

protected: // create from serialization only
	CEx24bView();
	DECLARE_DYNCREATE(CEx24bView)

// Attributes
public:
	CEx24bDoc* GetDocument() const;

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


BOOL DoPasteDib(COleDataObject* pDataObject);
void MoveTrackRect(CPoint point);
COleDataSource* SaveDib();

// Implementation
public:
	virtual ~CEx24bView();
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
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual void OnDragLeave();
    virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
    afx_msg void OnEditCopyto();
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
    afx_msg void OnEditPastefrom();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // debug version in Ex24bView.cpp
inline CEx24bDoc* CEx24bView::GetDocument() const
   { return reinterpret_cast<CEx24bDoc*>(m_pDocument); }
#endif

