// Ex05cDoc.h : interface of the CEx05cDoc class
//


#pragma once

class CEx05cDoc : public CDocument
{
protected: // create from serialization only
	CEx05cDoc();
	DECLARE_DYNCREATE(CEx05cDoc)

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
	virtual ~CEx05cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


