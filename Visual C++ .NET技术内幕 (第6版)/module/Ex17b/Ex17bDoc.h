// Ex17bDoc.h : interface of the CEx17bDoc class
//


#pragma once

typedef CArray<CRect, CRect&> CRectArray;

class CEx17bDoc : public CDocument
{
protected: // create from serialization only
	CEx17bDoc();
	DECLARE_DYNCREATE(CEx17bDoc)

// Attributes
public:

	enum { nLinesPerPage = 12 };
    enum { nMaxEllipses = 50 };
    CRectArray m_ellipseArray;

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEx17bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


