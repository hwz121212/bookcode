// Ex06cDoc.h : interface of the CEx06cDoc class
//


#pragma once

class CEx06cDoc : public CDocument
{
protected: // create from serialization only
	CEx06cDoc();
	DECLARE_DYNCREATE(CEx06cDoc)

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
	virtual ~CEx06cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


