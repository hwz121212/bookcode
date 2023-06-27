// ex28bView.h : interface of the CEx28bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28BVIEW_H__1EAAB6E1_6011_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX28BVIEW_H__1EAAB6E1_6011_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CF_OBJECTDESCRIPTOR	"Object Descriptor"
#define CF_EMBEDDEDOBJECT "Embedded Object"
#define SETFORMATETC(fe, cf, asp, td, med, li)   \
	((fe).cfFormat=cf, \
	 (fe).dwAspect=asp, \
	 (fe).ptd=td, \
	 (fe).tymed=med, \
	 (fe).lindex=li)

/////////////////////////////////////////////////////////////////////////////
class CEx28bView : public CScrollView
{
public:
	CLIPFORMAT m_cfObjDesc;
	CLIPFORMAT m_cfEmbedded;
	CSize m_sizeTotal;  // document size
	CRectTracker m_tracker;
	CRect m_rectTracker; // logical coords
protected: // create from serialization only
	CEx28bView();
	DECLARE_DYNCREATE(CEx28bView)

// Attributes
public:
	CEx28bDoc* GetDocument();

private:
	void GetSize();
	void SetNames();
	void SetViewAdvise();
	BOOL MakeMetafilePict(COleDataSource* pSource);
	COleDataSource* SaveObject();
	BOOL DoPasteObject(COleDataObject* pDataObject);
	BOOL DoPasteObjectDescriptor(COleDataObject* pDataObject);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28bView)
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyto();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPastefrom();
	afx_msg void OnEditInsertobject();
	afx_msg void OnUpdateEditInsertobject(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex28bView.cpp
inline CEx28bDoc* CEx28bView::GetDocument()
   { return (CEx28bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations 
//  immediately before the previous line.

#endif 
// !defined(AFX_EX28BVIEW_H__1EAAB6E1_6011_11D0_848F_00400526305B__INCLUDED_)
