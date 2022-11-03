// PoemDoc.h : interface of the CPoemDoc class
//


#pragma once

class CPoemDoc : public CDocument
{
protected: // create from serialization only
	CPoemDoc();
	DECLARE_DYNCREATE(CPoemDoc)

// Attributes
public:
    CStringArray m_stringArray;

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CPoemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual void DeleteContents();
};


