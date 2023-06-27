// ex15aDoc.h : interface of the CEx15aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX15ADOC_H__D332EB6D_B345_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX15ADOC_H__D332EB6D_B345_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx15aDoc : public CDocument
{
protected: // create from serialization only
	CEx15aDoc();
	DECLARE_DYNCREATE(CEx15aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx15aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx15aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx15aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX15ADOC_H__D332EB6D_B345_11D1_8ED7_0080C7360DC1__INCLUDED_)
