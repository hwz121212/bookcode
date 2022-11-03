// Ex13cDoc.h : interface of the CEx13cDoc class
//


#pragma once

class CEx13cDoc : public CDocument
{
protected: // create from serialization only
	CEx13cDoc();
	DECLARE_DYNCREATE(CEx13cDoc)

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
	virtual ~CEx13cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


