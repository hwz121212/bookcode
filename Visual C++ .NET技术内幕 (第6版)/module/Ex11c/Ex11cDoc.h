// Ex11cDoc.h : interface of the CEx11cDoc class
//


#pragma once

class CEx11cDoc : public CDocument
{
protected: // create from serialization only
	CEx11cDoc();
	DECLARE_DYNCREATE(CEx11cDoc)

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
	virtual ~CEx11cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


