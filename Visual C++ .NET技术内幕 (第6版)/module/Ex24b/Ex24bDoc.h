// Ex24bDoc.h : interface of the CEx24bDoc class
//


#pragma once

#include "cdib.h"

class CEx24bDoc : public CDocument
{
protected: // create from serialization only
	CEx24bDoc();
	DECLARE_DYNCREATE(CEx24bDoc)

// Attributes
public:
    CDib m_dib;
    BOOL m_bDragHere; // for drags between two wins linked to this doc

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEx24bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual void DeleteContents();
    afx_msg void OnEditClearall();
};


