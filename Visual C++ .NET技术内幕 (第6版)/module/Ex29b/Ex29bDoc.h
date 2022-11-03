// Ex29bDoc.h : interface of the CEx29bDoc class
//


#pragma once

class CEx29bDoc : public CDocument
{
protected: // create from serialization only
	CEx29bDoc();
	DECLARE_DYNCREATE(CEx29bDoc)

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
	virtual ~CEx29bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


