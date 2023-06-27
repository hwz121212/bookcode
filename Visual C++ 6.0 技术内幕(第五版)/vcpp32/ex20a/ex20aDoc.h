// ex20aDoc.h : interface of the CEx20aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX20ADOC_H__806617AD_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX20ADOC_H__806617AD_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx20aDoc : public CDocument
{
protected: // create from serialization only
	CEx20aDoc();
	DECLARE_DYNCREATE(CEx20aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx20aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx20aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx20aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX20ADOC_H__806617AD_C4C9_11D1_B30A_0080C7360DC1__INCLUDED_)
