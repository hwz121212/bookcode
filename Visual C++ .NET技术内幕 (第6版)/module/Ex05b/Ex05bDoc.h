// Ex05bDoc.h : interface of the CEx05bDoc class
//


#pragma once

class CEx05bDoc : public CDocument
{
protected: // create from serialization only
	CEx05bDoc();
	DECLARE_DYNCREATE(CEx05bDoc)

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
	virtual ~CEx05bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


