// novelView.h : interface of the CNovelView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOVELVIEW_H__68D9F56D_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_)
#define AFX_NOVELVIEW_H__68D9F56D_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNovelView : public CHtmlView
{
protected: // create from serialization only
	CNovelView();
	DECLARE_DYNCREATE(CNovelView)

// Attributes
public:
	CNovelDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNovelView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	CString site;
	virtual ~CNovelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNovelView)
	afx_msg void OnEditchangeCombosite();
	afx_msg void OnSelchangeCombosite();
	afx_msg void OnButtonsite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in novelView.cpp
inline CNovelDoc* CNovelView::GetDocument()
   { return (CNovelDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOVELVIEW_H__68D9F56D_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_)
