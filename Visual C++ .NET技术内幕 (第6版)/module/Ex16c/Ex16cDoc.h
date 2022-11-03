// Ex16cDoc.h : interface of the CEx16cDoc class
//


#pragma once

#include "student.h"

class CEx16cDoc : public CDocument
{
protected: // create from serialization only
	CEx16cDoc();
	DECLARE_DYNCREATE(CEx16cDoc)

// Attributes
public:
	CStudentList* GetList() {
        return &m_studentList;
    }

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEx16cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
    CStudentList m_studentList;

public:
    virtual void DeleteContents();
    afx_msg void OnEditClearall();
    afx_msg void OnUpdateEditClearall(CCmdUI *pCmdUI);
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
};


