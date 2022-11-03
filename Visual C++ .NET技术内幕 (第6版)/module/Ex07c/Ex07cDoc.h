// Ex07cDoc.h : interface of the CEx07cDoc class
//


#pragma once

class CEx07cDoc : public CDocument
{
protected: // create from serialization only
	CEx07cDoc();
	DECLARE_DYNCREATE(CEx07cDoc)

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
	virtual ~CEx07cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


