// ex27aDoc.h : interface of the CEx27aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27ADOC_H__F7547B2B_F63A_11D1_B30A_D09549C10710__INCLUDED_)
#define AFX_EX27ADOC_H__F7547B2B_F63A_11D1_B30A_D09549C10710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx27aDoc : public CDocument
{
protected: // create from serialization only
	CEx27aDoc();
	DECLARE_DYNCREATE(CEx27aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx27aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27ADOC_H__F7547B2B_F63A_11D1_B30A_D09549C10710__INCLUDED_)
