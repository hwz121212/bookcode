// Ex16aView.h : interface of the CEx16aView class
//


#pragma once


class CEx16aView : public CFormView
{
protected: // create from serialization only
	CEx16aView();
	DECLARE_DYNCREATE(CEx16aView)

public:
	enum{ IDD = IDD_EX16A_FORM };

// Attributes
public:
	CEx16aDoc* GetDocument() const;
protected:
    POSITION      m_position; // current position in document list
    CStudentList* m_pList;    // copied from document
// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CEx16aView();
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
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnStudentHome();
	afx_msg void OnStudentEnd();
	afx_msg void OnStudentPrevious();
	afx_msg void OnStudentNext();
	afx_msg void OnStudentInsert();
	afx_msg void OnStudentDelete();
	afx_msg void OnUpdateStudentHome(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStudentEnd(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStudentPrevious(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStudentNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStudentDelete(CCmdUI *pCmdUI);
	int m_nGrade;
    CString m_strName;
protected:
	virtual void OnUpdate(CView* /*pSender*/, 
		                  LPARAM /*lHint*/, CObject* /*pHint*/);
public:
    afx_msg void OnBnClickedClear();
};

#ifndef _DEBUG  // debug version in Ex16aView.cpp
inline CEx16aDoc* CEx16aView::GetDocument() const
   { return reinterpret_cast<CEx16aDoc*>(m_pDocument); }
#endif

