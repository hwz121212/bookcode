// FormColorDoc.h : interface of the CFormColorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMCOLORDOC_H__B7C92256_E459_11D2_A71D_A44E1A83F14B__INCLUDED_)
#define AFX_FORMCOLORDOC_H__B7C92256_E459_11D2_A71D_A44E1A83F14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFormColorDoc : public CDocument
{
protected: // create from serialization only
	CFormColorDoc();
	DECLARE_DYNCREATE(CFormColorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormColorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFormColorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormColorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCOLORDOC_H__B7C92256_E459_11D2_A71D_A44E1A83F14B__INCLUDED_)
