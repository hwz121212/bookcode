// Ex28aDoc.h : interface of the CEx28aDoc class
//


#pragma once

class CEx28aDoc : public CDocument
{
protected: // create from serialization only
	CEx28aDoc();
	DECLARE_DYNCREATE(CEx28aDoc)

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
	virtual ~CEx28aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


