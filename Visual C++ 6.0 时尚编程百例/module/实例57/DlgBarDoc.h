// DlgBarDoc.h : interface of the CDlgBarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGBARDOC_H__958A2899_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
#define AFX_DLGBARDOC_H__958A2899_DB28_11D2_A71D_D12047679B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDlgBarDoc : public CDocument
{
protected: // create from serialization only
	CDlgBarDoc();
	DECLARE_DYNCREATE(CDlgBarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgBarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBARDOC_H__958A2899_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
