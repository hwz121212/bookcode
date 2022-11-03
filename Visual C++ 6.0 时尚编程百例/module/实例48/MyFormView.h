// MyFormView.h : interface of the CMyFormView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFORMVIEW_H__5862DF62_DB10_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_MYFORMVIEW_H__5862DF62_DB10_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyFormView : public CFormView
{
protected: // create from serialization only
	CMyFormView();
	DECLARE_DYNCREATE(CMyFormView)
    CBitmap m_bitmap;
public:
	//{{AFX_DATA(CMyFormView)
	enum{ IDD = IDD_MYFORM_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CMyFormDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFormView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFormView)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFormView.cpp
inline CMyFormDoc* CMyFormView::GetDocument()
   { return (CMyFormDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFORMVIEW_H__5862DF62_DB10_11D2_A71D_B295A824025F__INCLUDED_)
