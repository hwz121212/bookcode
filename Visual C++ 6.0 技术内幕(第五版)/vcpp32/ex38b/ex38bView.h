// ex38bView.h : interface of the CEx38bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX38BVIEW_H__25B52B02_0533_11D2_8B47_00104B881C94__INCLUDED_)
#define AFX_EX38BVIEW_H__25B52B02_0533_11D2_8B47_00104B881C94__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx38bView : public CView
{
protected: // create from serialization only
	CEx38bView();
	DECLARE_DYNCREATE(CEx38bView)

// Attributes
public:
	CEx38bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx38bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx38bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx38bView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex38bView.cpp
inline CEx38bDoc* CEx38bView::GetDocument()
   { return (CEx38bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX38BVIEW_H__25B52B02_0533_11D2_8B47_00104B881C94__INCLUDED_)
