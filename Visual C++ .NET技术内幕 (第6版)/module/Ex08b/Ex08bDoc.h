// Ex08bDoc.h : interface of the CEx08bDoc class
//


#pragma once

class CEx08bDoc : public CDocument
{
protected: // create from serialization only
	CEx08bDoc();
	DECLARE_DYNCREATE(CEx08bDoc)

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
	virtual ~CEx08bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


