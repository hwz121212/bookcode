// Ex09aDoc.h : interface of the CEx09aDoc class
//


#pragma once

class CEx09aDoc : public CDocument
{
protected: // create from serialization only
	CEx09aDoc();
	DECLARE_DYNCREATE(CEx09aDoc)

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
	virtual ~CEx09aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


