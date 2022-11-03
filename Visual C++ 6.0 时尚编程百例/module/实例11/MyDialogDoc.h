// MyDialogDoc.h : interface of the CMyDialogDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDIALOGDOC_H__5466590E_114B_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYDIALOGDOC_H__5466590E_114B_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyDialogDoc : public CDocument
{
protected: // create from serialization only
	CMyDialogDoc();
	DECLARE_DYNCREATE(CMyDialogDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialogDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyDialogDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyDialogDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOGDOC_H__5466590E_114B_11D4_876D_00001CD613F0__INCLUDED_)
