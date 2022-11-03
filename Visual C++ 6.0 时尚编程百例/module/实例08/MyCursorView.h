// MyCursorView.h : interface of the CMyCursorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCURSORVIEW_H__3C96996D_0F2B_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYCURSORVIEW_H__3C96996D_0F2B_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyCursorView : public CView
{
protected: // create from serialization only
	CMyCursorView();
	DECLARE_DYNCREATE(CMyCursorView)

// Attributes
public:
	CMyCursorDoc* GetDocument();

// Operations
public:
	HCURSOR CUR;
protected:
	void LoadCursorID(UINT Cur);
    UINT CurName;
	void CapPoint(CPoint MousePos);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCursorView)
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
	virtual ~CMyCursorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCursorView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyCursorView.cpp
inline CMyCursorDoc* CMyCursorView::GetDocument()
   { return (CMyCursorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCURSORVIEW_H__3C96996D_0F2B_11D4_876D_00001CD613F0__INCLUDED_)
