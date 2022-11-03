// MyIeView.h : interface of the CMyIeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIEVIEW_H__BD65158D_C472_11D2_A71D_AFFC5B955368__INCLUDED_)
#define AFX_MYIEVIEW_H__BD65158D_C472_11D2_A71D_AFFC5B955368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyIeView : public CHtmlView
{
protected: // create from serialization only
	CMyIeView();
	DECLARE_DYNCREATE(CMyIeView)

// Attributes
public:
	CMyIeDoc* GetDocument();
	CString MyAddressStr;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyIeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyIeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyIeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnMyAddress(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyIeView.cpp
inline CMyIeDoc* CMyIeView::GetDocument()
   { return (CMyIeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIEVIEW_H__BD65158D_C472_11D2_A71D_AFFC5B955368__INCLUDED_)
