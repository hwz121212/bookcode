// ex38bDoc.h : interface of the CEx38bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX38BDOC_H__25B52B00_0533_11D2_8B47_00104B881C94__INCLUDED_)
#define AFX_EX38BDOC_H__25B52B00_0533_11D2_8B47_00104B881C94__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx38bDoc : public CDocument
{
protected: // create from serialization only
	CEx38bDoc();
	DECLARE_DYNCREATE(CEx38bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx38bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx38bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx38bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX38BDOC_H__25B52B00_0533_11D2_8B47_00104B881C94__INCLUDED_)
