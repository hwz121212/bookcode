// Ex15bDoc.h : interface of the CEx15bDoc class
//


#pragma once

#include "student.h"

class CEx15bDoc : public CDocument
{
protected: // create from serialization only
	CEx15bDoc();
	DECLARE_DYNCREATE(CEx15bDoc)

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
	virtual ~CEx15bDoc();
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
};


