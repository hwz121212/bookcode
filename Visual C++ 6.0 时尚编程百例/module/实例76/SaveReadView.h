// SaveReadView.h : interface of the CSaveReadView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVEREADVIEW_H__70B4B530_1DEE_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_SAVEREADVIEW_H__70B4B530_1DEE_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSaveReadView : public CFormView
{
protected: // create from serialization only
	CSaveReadView();
	DECLARE_DYNCREATE(CSaveReadView)

public:
	//{{AFX_DATA(CSaveReadView)
	enum { IDD = IDD_SAVEREAD_FORM };
	CComboBox	m_subject;
	float	m_score;
	CString	m_name;
	float	m_total;
	//}}AFX_DATA

// Attributes
public:
	CSaveReadDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveReadView)
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
	virtual ~CSaveReadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSaveReadView)
	afx_msg void OnChangeName();
	afx_msg void OnChangeScore();
	afx_msg void OnSelchangeSubject();
	afx_msg void OnText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SaveReadView.cpp
inline CSaveReadDoc* CSaveReadView::GetDocument()
   { return (CSaveReadDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEREADVIEW_H__70B4B530_1DEE_11D4_B0E6_00001A012804__INCLUDED_)
