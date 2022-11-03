// Ex13aDoc.h : interface of the CEx13aDoc class
//


#pragma once

class CEx13aDoc : public CDocument
{
protected: // create from serialization only
	CEx13aDoc();
	DECLARE_DYNCREATE(CEx13aDoc)

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
	virtual ~CEx13aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


