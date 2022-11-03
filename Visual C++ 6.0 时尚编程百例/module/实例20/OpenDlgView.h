// OpenDlgView.h : interface of the COpenDlgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENDLGVIEW_H__D04902A6_DB09_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_OPENDLGVIEW_H__D04902A6_DB09_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COpenDlgView : public CView
{
protected: // create from serialization only
	COpenDlgView();
	DECLARE_DYNCREATE(COpenDlgView)

// Attributes
public:
	COpenDlgDoc* GetDocument();
    CString FilePathname;
    CString FileName;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenDlgView)
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
	virtual ~COpenDlgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COpenDlgView)
	afx_msg void OnFileopen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OpenDlgView.cpp
inline COpenDlgDoc* COpenDlgView::GetDocument()
   { return (COpenDlgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENDLGVIEW_H__D04902A6_DB09_11D2_A71D_B295A824025F__INCLUDED_)
