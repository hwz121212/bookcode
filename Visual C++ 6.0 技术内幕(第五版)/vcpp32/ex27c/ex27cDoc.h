// ex27cDoc.h : interface of the CEx27cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27CDOC_H__624519A7_F64F_11D1_B30A_D09549C10710__INCLUDED_)
#define AFX_EX27CDOC_H__624519A7_F64F_11D1_B30A_D09549C10710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx27cDoc : public CDocument
{
protected: // create from serialization only
	CEx27cDoc();
	DECLARE_DYNCREATE(CEx27cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx27cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27CDOC_H__624519A7_F64F_11D1_B30A_D09549C10710__INCLUDED_)
