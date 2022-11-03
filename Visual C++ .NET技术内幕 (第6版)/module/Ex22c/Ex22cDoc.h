// Ex22cDoc.h : interface of the CEx22cDoc class
//


#pragma once

class CEx22cDoc : public CDocument
{
protected: // create from serialization only
	CEx22cDoc();
	DECLARE_DYNCREATE(CEx22cDoc)

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
	virtual ~CEx22cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


