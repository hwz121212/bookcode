// Ex06dDoc.h : interface of the CEx06dDoc class
//


#pragma once

class CEx06dDoc : public CDocument
{
protected: // create from serialization only
	CEx06dDoc();
	DECLARE_DYNCREATE(CEx06dDoc)

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
	virtual ~CEx06dDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


