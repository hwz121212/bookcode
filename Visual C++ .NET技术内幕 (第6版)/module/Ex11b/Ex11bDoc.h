// Ex11bDoc.h : interface of the CEx11bDoc class
//


#pragma once

class CEx11bDoc : public CDocument
{
protected: // create from serialization only
	CEx11bDoc();
	DECLARE_DYNCREATE(CEx11bDoc)

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
	virtual ~CEx11bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


