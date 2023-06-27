// ex11aView.h : interface of the CEx11aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11AVIEW_H__5706E3AD_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX11AVIEW_H__5706E3AD_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx11aView : public CScrollView
{
protected: // create from serialization only
	CEx11aView();
	DECLARE_DYNCREATE(CEx11aView)

// Attributes
public:
	CEx11aDoc* GetDocument();
	CDC*     m_pdcMemory;
	CBitmap* m_pBitmap;
	CSize    m_sizeSource, m_sizeDest;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex11aView.cpp
inline CEx11aDoc* CEx11aView::GetDocument()
   { return (CEx11aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11AVIEW_H__5706E3AD_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_)
