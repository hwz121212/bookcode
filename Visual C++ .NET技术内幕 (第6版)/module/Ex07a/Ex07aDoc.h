// Ex07aDoc.h : interface of the CEx07aDoc class
//


#pragma once

class CEx07aDoc : public CDocument
{
protected: // create from serialization only
	CEx07aDoc();
	DECLARE_DYNCREATE(CEx07aDoc)

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
	virtual ~CEx07aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


