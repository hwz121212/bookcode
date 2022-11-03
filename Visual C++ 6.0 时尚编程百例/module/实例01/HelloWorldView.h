// HelloWorldView.h : interface of the CHelloWorldView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELLOWORLDVIEW_H__A1700798_E3C2_11D2_A71D_ED13154A5A4B__INCLUDED_)
#define AFX_HELLOWORLDVIEW_H__A1700798_E3C2_11D2_A71D_ED13154A5A4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHelloWorldView : public CView
{
protected: // create from serialization only
	CHelloWorldView();
	DECLARE_DYNCREATE(CHelloWorldView)

// Attributes
public:
	CHelloWorldDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelloWorldView)
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
	virtual ~CHelloWorldView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHelloWorldView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HelloWorldView.cpp
inline CHelloWorldDoc* CHelloWorldView::GetDocument()
   { return (CHelloWorldDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELLOWORLDVIEW_H__A1700798_E3C2_11D2_A71D_ED13154A5A4B__INCLUDED_)
