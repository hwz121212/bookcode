// ex26bView.h : interface of the CEx26bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26BVIEW_H__4D1ED006_01E1_11D2_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX26BVIEW_H__4D1ED006_01E1_11D2_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx26bView : public CScrollView
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
	CEx26bView();
	DECLARE_DYNCREATE(CEx26bView)

// Attributes
public:
	CEx26bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate();
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26bView)
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyto();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPastefrom();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    BOOL DoPasteDib(COleDataObject* pDataObject);
    COleDataSource* SaveDib();
    void MoveTrackRect(CPoint point);
};

#ifndef _DEBUG  // debug version in ex26bView.cpp
inline CEx26bDoc* CEx26bView::GetDocument()
   { return (CEx26bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26BVIEW_H__4D1ED006_01E1_11D2_B30A_0080C7360DC1__INCLUDED_)
