// Ex23eDoc.h : interface of the CEx23eDoc class
//


#pragma once

class CEx23eDoc : public CDocument
{
protected: // create from serialization only
	CEx23eDoc();
	DECLARE_DYNCREATE(CEx23eDoc)

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
	virtual ~CEx23eDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


