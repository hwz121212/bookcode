// DynMenuDoc.h : interface of the CDynMenuDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNMENUDOC_H__6ABF34EB_E453_11D2_A71D_A44E1A83F14B__INCLUDED_)
#define AFX_DYNMENUDOC_H__6ABF34EB_E453_11D2_A71D_A44E1A83F14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDynMenuDoc : public CDocument
{
protected: // create from serialization only
	CDynMenuDoc();
	DECLARE_DYNCREATE(CDynMenuDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynMenuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDynMenuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDynMenuDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNMENUDOC_H__6ABF34EB_E453_11D2_A71D_A44E1A83F14B__INCLUDED_)
