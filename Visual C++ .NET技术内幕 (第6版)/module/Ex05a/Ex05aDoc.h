// Ex05aDoc.h : interface of the CEx05aDoc class
//


#pragma once

class CEx05aDoc : public CDocument
{
protected: // create from serialization only
	CEx05aDoc();
	DECLARE_DYNCREATE(CEx05aDoc)

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
	virtual ~CEx05aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


