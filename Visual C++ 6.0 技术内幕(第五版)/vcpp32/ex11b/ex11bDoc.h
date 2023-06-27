// ex11bDoc.h : interface of the CEx11bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11BDOC_H__5706E3C1_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX11BDOC_H__5706E3C1_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx11bDoc : public CDocument
{
protected: // create from serialization only
	CEx11bDoc();
	DECLARE_DYNCREATE(CEx11bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11BDOC_H__5706E3C1_A6D1_11D1_8ED7_0080C7360DC1__INCLUDED_)
