// ex37aView.h : interface of the CEx37aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX37AVIEW_H__97DB124F_0651_11D2_8524_444553540000__INCLUDED_)
#define AFX_EX37AVIEW_H__97DB124F_0651_11D2_8524_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx37aView : public CHtmlView
{
protected: // create from serialization only
	CEx37aView();
	DECLARE_DYNCREATE(CEx37aView)

// Attributes
public:
	CEx37aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx37aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx37aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx37aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex37aView.cpp
inline CEx37aDoc* CEx37aView::GetDocument()
   { return (CEx37aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX37AVIEW_H__97DB124F_0651_11D2_8524_444553540000__INCLUDED_)
