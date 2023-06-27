// StuView.h : interface of the CStudentView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STUVIEW_H__3CC6840F_B8FB_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_STUVIEW_H__3CC6840F_B8FB_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStudentView : public CFormView
{
protected:
    POSITION      m_position; // current position in document list
    CStudentList* m_pList;    // copied from document

protected: // create from serialization only
	CStudentView();
	DECLARE_DYNCREATE(CStudentView)

public:
	//{{AFX_DATA(CStudentView)
	enum { IDD = IDD_STUDENT };
	int		m_nGrade;
	CString	m_strName;
	//}}AFX_DATA

// Attributes
public:
	CStudentDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStudentView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStudentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual void ClearEntry();
    virtual void InsertEntry(POSITION position);
    virtual void GetEntry(POSITION position);

// Generated message map functions
protected:
	//{{AFX_MSG(CStudentView)
	afx_msg void OnClear();
	afx_msg void OnStudentHome();
	afx_msg void OnStudentEnd();
	afx_msg void OnStudentPrev();
	afx_msg void OnStudentNext();
	afx_msg void OnStudentIns();
	afx_msg void OnStudentDel();
	afx_msg void OnUpdateStudentHome(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStudentEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStudentDel(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StuView.cpp
inline CStudentDoc* CStudentView::GetDocument()
   { return (CStudentDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STUVIEW_H__3CC6840F_B8FB_11D1_8ED7_0080C7360DC1__INCLUDED_)
