// Font1View.h : interface of the CFont1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONT1VIEW_H__BAE6D14C_12FA_11D4_A927_00001A012804__INCLUDED_)
#define AFX_FONT1VIEW_H__BAE6D14C_12FA_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFont1View : public CView
{
protected: // create from serialization only
	CFont1View();
	DECLARE_DYNCREATE(CFont1View)

// Attributes
public:
	CFont1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFont1View)
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
	virtual ~CFont1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFont1View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Font1View.cpp
inline CFont1Doc* CFont1View::GetDocument()
   { return (CFont1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONT1VIEW_H__BAE6D14C_12FA_11D4_A927_00001A012804__INCLUDED_)
