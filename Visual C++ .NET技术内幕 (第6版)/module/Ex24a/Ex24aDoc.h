// Ex24aDoc.h : interface of the CEx24aDoc class
//


#pragma once

#include "cdib.h"

class CEx24aDoc : public CDocument
{
public:
    CDib m_dib;

protected: // create from serialization only
	CEx24aDoc();
	DECLARE_DYNCREATE(CEx24aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEx24aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEditClearall();
    afx_msg void OnUpdateEditClearall(CCmdUI *pCmdUI);
    virtual void DeleteContents();
};


