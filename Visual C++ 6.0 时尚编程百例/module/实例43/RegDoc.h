// RegDoc.h : interface of the CRegDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGDOC_H__D049028B_DB09_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_REGDOC_H__D049028B_DB09_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRegDoc : public CDocument
{
protected: // create from serialization only
	CRegDoc();
	DECLARE_DYNCREATE(CRegDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRegDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRegDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDOC_H__D049028B_DB09_11D2_A71D_B295A824025F__INCLUDED_)
