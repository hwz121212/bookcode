// DlgBarView.h : interface of the CDlgBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGBARVIEW_H__958A289B_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
#define AFX_DLGBARVIEW_H__958A289B_DB28_11D2_A71D_D12047679B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDlgBarView : public CView
{
protected: // create from serialization only
	CDlgBarView();
	DECLARE_DYNCREATE(CDlgBarView)

// Attributes
public:
	CDlgBarDoc* GetDocument();
    void ShowBitmap(CString Bmpname);
		
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBarView)
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
	virtual ~CDlgBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgBarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnButtonClicked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DlgBarView.cpp
inline CDlgBarDoc* CDlgBarView::GetDocument()
   { return (CDlgBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBARVIEW_H__958A289B_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
