// MyDialogBarView.h : interface of the CMyDialogBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDIALOGBARVIEW_H__395A492D_DEB9_11D2_A71D_F0C8D02E405B__INCLUDED_)
#define AFX_MYDIALOGBARVIEW_H__395A492D_DEB9_11D2_A71D_F0C8D02E405B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyDialogBarView : public CView
{
protected: // create from serialization only
	CMyDialogBarView();
	DECLARE_DYNCREATE(CMyDialogBarView)

// Attributes
public:
	CMyDialogBarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialogBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyDialogBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyDialogBarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyDialogBarView.cpp
inline CMyDialogBarDoc* CMyDialogBarView::GetDocument()
   { return (CMyDialogBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOGBARVIEW_H__395A492D_DEB9_11D2_A71D_F0C8D02E405B__INCLUDED_)
