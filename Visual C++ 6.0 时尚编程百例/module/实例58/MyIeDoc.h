// MyIeDoc.h : interface of the CMyIeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIEDOC_H__BD65158B_C472_11D2_A71D_AFFC5B955368__INCLUDED_)
#define AFX_MYIEDOC_H__BD65158B_C472_11D2_A71D_AFFC5B955368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyIeDoc : public CDocument
{
protected: // create from serialization only
	CMyIeDoc();
	DECLARE_DYNCREATE(CMyIeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyIeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyIeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyIeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIEDOC_H__BD65158B_C472_11D2_A71D_AFFC5B955368__INCLUDED_)
