// MouseClickDoc.h : interface of the CMouseClickDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSECLICKDOC_H__34D8A45F_0B96_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MOUSECLICKDOC_H__34D8A45F_0B96_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMouseClickDoc : public CDocument
{
protected: // create from serialization only
	CMouseClickDoc();
	DECLARE_DYNCREATE(CMouseClickDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseClickDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMouseClickDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMouseClickDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSECLICKDOC_H__34D8A45F_0B96_11D4_876D_00001CD613F0__INCLUDED_)
