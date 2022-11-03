// Ex23dDoc.h : interface of the CEx23dDoc class
//


#pragma once

class CEx23dDoc : public CDocument
{
protected: // create from serialization only
	CEx23dDoc();
	DECLARE_DYNCREATE(CEx23dDoc)

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
	virtual ~CEx23dDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


