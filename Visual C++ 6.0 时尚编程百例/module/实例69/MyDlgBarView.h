// MyDlgBarView.h : interface of the CMyDlgBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDLGBARVIEW_H__3F1C89ED_C384_11D2_A71D_D06875665969__INCLUDED_)
#define AFX_MYDLGBARVIEW_H__3F1C89ED_C384_11D2_A71D_D06875665969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyDlgBarView : public CView
{
protected: // create from serialization only
	CMyDlgBarView();
	DECLARE_DYNCREATE(CMyDlgBarView)

// Attributes
public:
	CMyDlgBarDoc* GetDocument();

// Operations
public:
	CBitmap MyBitmap1,MyBitmap2,MyBitmap3,MyBitmap4;
	int MyBitmapID;
	void SetMyBitmapID(int id);
	int LoadMyBitmapID();
	
	
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgBarView)
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
	virtual ~CMyDlgBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyDlgBarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnChioce(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyDlgBarView.cpp
inline CMyDlgBarDoc* CMyDlgBarView::GetDocument()
   { return (CMyDlgBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGBARVIEW_H__3F1C89ED_C384_11D2_A71D_D06875665969__INCLUDED_)
