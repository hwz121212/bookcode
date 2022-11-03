// ListboxDoc.h : interface of the CListboxDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTBOXDOC_H__9859BEBE_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
#define AFX_LISTBOXDOC_H__9859BEBE_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CListboxDoc : public CDocument
{
protected: // create from serialization only
	CListboxDoc();
	DECLARE_DYNCREATE(CListboxDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListboxDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListboxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListboxDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXDOC_H__9859BEBE_C5B0_11D2_A71D_E1F8995C8269__INCLUDED_)
