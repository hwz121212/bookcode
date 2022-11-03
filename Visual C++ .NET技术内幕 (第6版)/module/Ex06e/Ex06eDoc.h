// Ex06eDoc.h : interface of the CEx06eDoc class
//


#pragma once

class CEx06eDoc : public CDocument
{
protected: // create from serialization only
	CEx06eDoc();
	DECLARE_DYNCREATE(CEx06eDoc)

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
	virtual ~CEx06eDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


