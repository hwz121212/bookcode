// ex16aDoc.h : interface of the CEx16aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX16ADOC_H__8115D80D_B454_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX16ADOC_H__8115D80D_B454_11D1_8ED7_0080C7360DC1__INCLUDED_

#include "Student.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx16aDoc : public CDocument
{
protected: // create from serialization only
	CEx16aDoc();
	DECLARE_DYNCREATE(CEx16aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx16aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CStudent m_student;
	virtual ~CEx16aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx16aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX16ADOC_H__8115D80D_B454_11D1_8ED7_0080C7360DC1__INCLUDED_)
