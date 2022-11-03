// Ex06aDoc.h : interface of the CEx06aDoc class
//


#pragma once

class CEx06aDoc : public CDocument
{
protected: // create from serialization only
	CEx06aDoc();
	DECLARE_DYNCREATE(CEx06aDoc)

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
	virtual ~CEx06aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


