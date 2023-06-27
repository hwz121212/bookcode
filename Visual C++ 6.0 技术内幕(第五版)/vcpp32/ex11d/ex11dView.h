// ex11dView.h : interface of the CEx11dView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11DVIEW_H__A2BB8E0F_A847_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX11DVIEW_H__A2BB8E0F_A847_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx11dView : public CView
{
protected: // create from serialization only
	CEx11dView();
	DECLARE_DYNCREATE(CEx11dView)

// Attributes
public:
	CEx11dDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11dView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11dView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11dView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex11dView.cpp
inline CEx11dDoc* CEx11dView::GetDocument()
   { return (CEx11dDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11DVIEW_H__A2BB8E0F_A847_11D1_8ED7_0080C7360DC1__INCLUDED_)
