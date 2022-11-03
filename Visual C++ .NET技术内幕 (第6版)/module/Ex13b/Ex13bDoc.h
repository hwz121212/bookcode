// Ex13bDoc.h : interface of the CEx13bDoc class
//


#pragma once

class CEx13bDoc : public CDocument
{
protected: // create from serialization only
	CEx13bDoc();
	DECLARE_DYNCREATE(CEx13bDoc)

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
	virtual ~CEx13bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


