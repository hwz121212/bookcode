// MyDialogBarDoc.h : interface of the CMyDialogBarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDIALOGBARDOC_H__395A492B_DEB9_11D2_A71D_F0C8D02E405B__INCLUDED_)
#define AFX_MYDIALOGBARDOC_H__395A492B_DEB9_11D2_A71D_F0C8D02E405B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyDialogBarDoc : public CDocument
{
protected: // create from serialization only
	CMyDialogBarDoc();
	DECLARE_DYNCREATE(CMyDialogBarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialogBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyDialogBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyDialogBarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOGBARDOC_H__395A492B_DEB9_11D2_A71D_F0C8D02E405B__INCLUDED_)
