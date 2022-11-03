// ListBoxView.h : interface of the CListBoxView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTBOXVIEW_H__443D6EAD_D930_11D2_A71D_B5732A6A165F__INCLUDED_)
#define AFX_LISTBOXVIEW_H__443D6EAD_D930_11D2_A71D_B5732A6A165F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CListBoxView : public CView
{
protected: // create from serialization only
	CListBoxView();
	DECLARE_DYNCREATE(CListBoxView)

// Attributes
public:
	CListBoxDoc* GetDocument();
 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxView)
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
	virtual ~CListBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ListBoxView.cpp
inline CListBoxDoc* CListBoxView::GetDocument()
   { return (CListBoxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXVIEW_H__443D6EAD_D930_11D2_A71D_B5732A6A165F__INCLUDED_)
