// ex37bView.h : interface of the CEx37bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX37BVIEW_H__97DB1279_0651_11D2_8524_444553540000__INCLUDED_)
#define AFX_EX37BVIEW_H__97DB1279_0651_11D2_8524_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx37bView : public CHtmlView
{
protected: // create from serialization only
	CEx37bView();
	DECLARE_DYNCREATE(CEx37bView)

// Attributes
public:
	CEx37bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx37bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx37bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx37bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex37bView.cpp
inline CEx37bDoc* CEx37bView::GetDocument()
   { return (CEx37bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX37BVIEW_H__97DB1279_0651_11D2_8524_444553540000__INCLUDED_)
