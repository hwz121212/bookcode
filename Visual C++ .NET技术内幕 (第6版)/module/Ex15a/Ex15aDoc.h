// Ex15aDoc.h : interface of the CEx15aDoc class
//


#pragma once

#include "student.h"

class CEx15aDoc : public CDocument
{
protected: // create from serialization only
	CEx15aDoc();
	DECLARE_DYNCREATE(CEx15aDoc)

// Attributes
public:
	CStudent m_student;
// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEx15aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


