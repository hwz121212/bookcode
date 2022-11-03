// ShowBmpView.h : interface of the CShowBmpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWBMPVIEW_H__958A28B4_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
#define AFX_SHOWBMPVIEW_H__958A28B4_DB28_11D2_A71D_D12047679B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShowBmpView : public CView
{
protected: // create from serialization only
	CShowBmpView();
	DECLARE_DYNCREATE(CShowBmpView)

// Attributes
public:
	CShowBmpDoc* GetDocument();
	int State;
    CString Bmpname;
	void Showpicture(CString Bmpname);
	CBitmap m_bitmap;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowBmpView)
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
	virtual ~CShowBmpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShowBmpView)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ShowBmpView.cpp
inline CShowBmpDoc* CShowBmpView::GetDocument()
   { return (CShowBmpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWBMPVIEW_H__958A28B4_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
