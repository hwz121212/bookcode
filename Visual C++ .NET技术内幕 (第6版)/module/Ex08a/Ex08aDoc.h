// Ex08aDoc.h : interface of the CEx08aDoc class
//


#pragma once

class CEx08aDoc : public CDocument
{
protected: // create from serialization only
	CEx08aDoc();
	DECLARE_DYNCREATE(CEx08aDoc)

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
	virtual ~CEx08aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


