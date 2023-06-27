// ex16aView.h : interface of the CEx16aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX16AVIEW_H__8115D80F_B454_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX16AVIEW_H__8115D80F_B454_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx16aView : public CFormView
{
protected: // create from serialization only
	CEx16aView();
	DECLARE_DYNCREATE(CEx16aView)

public:
	//{{AFX_DATA(CEx16aView)
	enum { IDD = IDD_EX16A_FORM };
	int		m_nGrade;
	CString	m_strName;
	//}}AFX_DATA

// Attributes
public:
	CEx16aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx16aView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx16aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx16aView)
	afx_msg void OnEnter();
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateControlsFromDoc();
};

#ifndef _DEBUG  // debug version in ex16aView.cpp
inline CEx16aDoc* CEx16aView::GetDocument()
   { return (CEx16aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX16AVIEW_H__8115D80F_B454_11D1_8ED7_0080C7360DC1__INCLUDED_)
