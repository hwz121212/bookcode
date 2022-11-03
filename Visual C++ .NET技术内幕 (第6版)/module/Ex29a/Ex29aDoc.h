// Ex29aDoc.h : interface of the CEx29aDoc class
//


#pragma once

class CEx29aDoc : public CDocument
{
protected: // create from serialization only
	CEx29aDoc();
	DECLARE_DYNCREATE(CEx29aDoc)

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
	virtual ~CEx29aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


