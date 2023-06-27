// ex09aDoc.h : interface of the CEx09aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX09ADOC_H__E0A2E3DD_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
#define AFX_EX09ADOC_H__E0A2E3DD_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx09aDoc : public CDocument
{
protected: // create from serialization only
	CEx09aDoc();
	DECLARE_DYNCREATE(CEx09aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx09aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx09aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx09aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX09ADOC_H__E0A2E3DD_D7BF_11D1_B2A3_FB06F1BF1F48__INCLUDED_)
