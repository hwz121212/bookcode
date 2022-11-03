// Ex03aDoc.h : interface of the CEx03aDoc class
//


#pragma once

class CEx03aDoc : public CDocument
{
protected: // create from serialization only
	CEx03aDoc();
	DECLARE_DYNCREATE(CEx03aDoc)

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
	virtual ~CEx03aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


