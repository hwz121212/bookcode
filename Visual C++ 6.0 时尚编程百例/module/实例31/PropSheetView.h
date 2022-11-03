// PropSheetView.h : interface of the CPropSheetView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPSHEETVIEW_H__682A1ECC_1396_11D4_A927_00001A012804__INCLUDED_)
#define AFX_PROPSHEETVIEW_H__682A1ECC_1396_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPropSheetView : public CView
{
protected: // create from serialization only
	CPropSheetView();
	DECLARE_DYNCREATE(CPropSheetView)

// Attributes
public:
	CPropSheetDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropSheetView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropSheetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPropSheetView)
	afx_msg void OnSheet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PropSheetView.cpp
inline CPropSheetDoc* CPropSheetView::GetDocument()
   { return (CPropSheetDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPSHEETVIEW_H__682A1ECC_1396_11D4_A927_00001A012804__INCLUDED_)
