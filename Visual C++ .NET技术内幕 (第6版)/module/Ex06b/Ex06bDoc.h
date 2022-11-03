// Ex06bDoc.h : interface of the CEx06bDoc class
//


#pragma once

class CEx06bDoc : public CDocument
{
protected: // create from serialization only
	CEx06bDoc();
	DECLARE_DYNCREATE(CEx06bDoc)

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
	virtual ~CEx06bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


