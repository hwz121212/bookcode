// ex24cView.h : interface of the CEx24cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX24CVIEW_H__4F329AFB_5DF1_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX24CVIEW_H__4F329AFB_5DF1_11D0_848F_00400526305B__INCLUDED_

class CEx24cView : public CView
{
protected: // create from serialization only
	CEx24cView();
	DECLARE_DYNCREATE(CEx24cView)

// Attributes
public:
	CEx24cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx24cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx24cView)
	afx_msg void OnTestSpaceship();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex24cView.cpp
inline CEx24cDoc* CEx24cView::GetDocument()
   { return (CEx24cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX24CVIEW_H__4F329AFB_5DF1_11D0_848F_00400526305B__INCLUDED_)
