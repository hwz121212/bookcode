// ex11bView.h : interface of the CEx11bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11BVIEW_H__5706E3C3_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX11BVIEW_H__5706E3C3_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx11bView : public CScrollView
{
protected: // create from serialization only
	CEx11bView();
	DECLARE_DYNCREATE(CEx11bView)

private:
    const CSize m_sizeEllipse;
    CPoint   m_pointTopLeft;
    BOOL     m_bCaptured;
    CSize    m_sizeOffset;
    CDC*     m_pdcMemory;
    CBitmap* m_pBitmap;

// Attributes
public:
	CEx11bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11bView)
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
	virtual ~CEx11bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex11bView.cpp
inline CEx11bDoc* CEx11bView::GetDocument()
   { return (CEx11bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11BVIEW_H__5706E3C3_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_)
