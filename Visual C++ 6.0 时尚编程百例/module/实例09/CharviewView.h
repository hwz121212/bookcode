// CharviewView.h : interface of the CCharviewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARVIEWVIEW_H__96F07F2C_1480_11D4_A927_00001A012804__INCLUDED_)
#define AFX_CHARVIEWVIEW_H__96F07F2C_1480_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCharviewView : public CView
{
protected: // create from serialization only
	CCharviewView();
	DECLARE_DYNCREATE(CCharviewView)

// Attributes
public:
	CCharviewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharviewView)
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

	virtual ~CCharviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCharviewView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CharviewView.cpp
inline CCharviewDoc* CCharviewView::GetDocument()
   { return (CCharviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARVIEWVIEW_H__96F07F2C_1480_11D4_A927_00001A012804__INCLUDED_)
