// MyRectDoc.h : interface of the CMyRectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYRECTDOC_H__E4283EEB_E4FC_11D2_A71D_94699A96D749__INCLUDED_)
#define AFX_MYRECTDOC_H__E4283EEB_E4FC_11D2_A71D_94699A96D749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyRectDoc : public CDocument
{
protected: // create from serialization only
	CMyRectDoc();
	DECLARE_DYNCREATE(CMyRectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyRectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyRectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYRECTDOC_H__E4283EEB_E4FC_11D2_A71D_94699A96D749__INCLUDED_)
