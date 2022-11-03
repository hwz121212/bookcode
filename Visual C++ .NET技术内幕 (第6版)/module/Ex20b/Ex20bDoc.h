// Ex20bDoc.h : interface of the CEx20bDoc class
//


#pragma once

class CEx20bDoc : public CDocument
{
protected: // create from serialization only
	CEx20bDoc();
	DECLARE_DYNCREATE(CEx20bDoc)

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
	virtual ~CEx20bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


