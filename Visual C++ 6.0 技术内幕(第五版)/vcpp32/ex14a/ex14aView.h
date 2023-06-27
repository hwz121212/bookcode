// ex14aView.h : interface of the CEx14aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX14AVIEW_H__361E214F_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX14AVIEW_H__361E214F_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx14aView : public CView
{
protected: // create from serialization only
	CEx14aView();
	DECLARE_DYNCREATE(CEx14aView)

// Attributes
public:
	CEx14aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx14aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx14aView)
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnDrawPattern();
	afx_msg void OnUpdateDrawPattern(CCmdUI* pCmdUI);
	afx_msg void OnDrawSquare();
	afx_msg void OnUpdateDrawSquare(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CRect m_rect;
    BOOL  m_bCircle;
    BOOL  m_bPattern;
};

#ifndef _DEBUG  // debug version in ex14aView.cpp
inline CEx14aDoc* CEx14aView::GetDocument()
   { return (CEx14aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14AVIEW_H__361E214F_B1BB_11D1_8ED7_0080C7360DC1__INCLUDED_)
