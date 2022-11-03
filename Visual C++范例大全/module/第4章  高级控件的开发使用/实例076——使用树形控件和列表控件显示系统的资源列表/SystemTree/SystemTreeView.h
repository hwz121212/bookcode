// SystemTreeView.h : interface of the CSystemTreeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMTREEVIEW_H__33EB8818_F961_43EA_8C63_0DC6CE7EAA24__INCLUDED_)
#define AFX_SYSTEMTREEVIEW_H__33EB8818_F961_43EA_8C63_0DC6CE7EAA24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSystemTreeView : public CView
{
protected: // create from serialization only
	CSystemTreeView();
	DECLARE_DYNCREATE(CSystemTreeView)

// Attributes
public:
	CSystemTreeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemTreeView)
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
	virtual ~CSystemTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSystemTreeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SystemTreeView.cpp
inline CSystemTreeDoc* CSystemTreeView::GetDocument()
   { return (CSystemTreeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMTREEVIEW_H__33EB8818_F961_43EA_8C63_0DC6CE7EAA24__INCLUDED_)
