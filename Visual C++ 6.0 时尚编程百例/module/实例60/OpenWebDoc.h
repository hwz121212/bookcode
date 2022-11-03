// OpenWebDoc.h : interface of the COpenWebDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENWEBDOC_H__804DDF8B_E1D0_11D2_A71D_89C2F5392855__INCLUDED_)
#define AFX_OPENWEBDOC_H__804DDF8B_E1D0_11D2_A71D_89C2F5392855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COpenWebDoc : public CDocument
{
protected: // create from serialization only
	COpenWebDoc();
	DECLARE_DYNCREATE(COpenWebDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenWebDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenWebDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COpenWebDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENWEBDOC_H__804DDF8B_E1D0_11D2_A71D_89C2F5392855__INCLUDED_)
