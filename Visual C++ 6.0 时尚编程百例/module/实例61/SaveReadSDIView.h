// SaveReadSDIView.h : interface of the CSaveReadSDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVEREADSDIVIEW_H__51C3F70C_1EB8_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_SAVEREADSDIVIEW_H__51C3F70C_1EB8_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSaveReadSDIView : public CFormView
{
protected: // create from serialization only
	CSaveReadSDIView();
	DECLARE_DYNCREATE(CSaveReadSDIView)

public:
	//{{AFX_DATA(CSaveReadSDIView)
	enum { IDD = IDD_SAVEREADSDI_FORM };
	CComboBox	m_subject;
	CString	m_name;
	float	m_score;
	float	m_total;
	//}}AFX_DATA

// Attributes
public:
	CSaveReadSDIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveReadSDIView)
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
	virtual ~CSaveReadSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSaveReadSDIView)
	afx_msg void OnChangeName();
	afx_msg void OnChangeScore();
	afx_msg void OnSelchangeSubject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SaveReadSDIView.cpp
inline CSaveReadSDIDoc* CSaveReadSDIView::GetDocument()
   { return (CSaveReadSDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEREADSDIVIEW_H__51C3F70C_1EB8_11D4_B0E6_00001A012804__INCLUDED_)
