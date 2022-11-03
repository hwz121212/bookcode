// Ex07bDoc.h : interface of the CEx07bDoc class
//


#pragma once

class CEx07bDoc : public CDocument
{
protected: // create from serialization only
	CEx07bDoc();
	DECLARE_DYNCREATE(CEx07bDoc)

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
	virtual ~CEx07bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


