// StuDoc.h : interface of the CStudentDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STUDOC_H__3CC6840D_B8FB_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_STUDOC_H__3CC6840D_B8FB_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "student.h"

class CStudentDoc : public CDocument
{
protected: // create from serialization only
	CStudentDoc();
	DECLARE_DYNCREATE(CStudentDoc)

// Attributes
public:
    CStudentList* GetList() {
        return &m_studentList;
    }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStudentDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStudentDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStudentDoc)
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CStudentList m_studentList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STUDOC_H__3CC6840D_B8FB_11D1_8ED7_0080C7360DC1__INCLUDED_)
