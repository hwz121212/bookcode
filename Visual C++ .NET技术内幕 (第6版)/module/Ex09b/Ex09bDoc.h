// Ex09bDoc.h : interface of the CEx09bDoc class
//


#pragma once

class CEx09bDoc : public CDocument
{
protected: // create from serialization only
	CEx09bDoc();
	DECLARE_DYNCREATE(CEx09bDoc)

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
	virtual ~CEx09bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


