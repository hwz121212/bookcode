// FormColorView.h : interface of the CFormColorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMCOLORVIEW_H__B7C92258_E459_11D2_A71D_A44E1A83F14B__INCLUDED_)
#define AFX_FORMCOLORVIEW_H__B7C92258_E459_11D2_A71D_A44E1A83F14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFormColorView : public CFormView
{
protected: // create from serialization only
	CFormColorView();
	DECLARE_DYNCREATE(CFormColorView)

public:
	//{{AFX_DATA(CFormColorView)
	enum { IDD = IDD_FORMCOLOR_FORM };
	CString	m_string;
	//}}AFX_DATA

// Attributes
public:
	CFormColorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormColorView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFormColorView();
	COLORREF m_pColor;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormColorView)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg void OnChioce(UINT nID);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FormColorView.cpp
inline CFormColorDoc* CFormColorView::GetDocument()
   { return (CFormColorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCOLORVIEW_H__B7C92258_E459_11D2_A71D_A44E1A83F14B__INCLUDED_)
