// PC2PCDoc.h : interface of the CPC2PCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PC2PCDOC_H__87A631F8_763A_45FD_A98F_B86D8CA18232__INCLUDED_)
#define AFX_PC2PCDOC_H__87A631F8_763A_45FD_A98F_B86D8CA18232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPC2PCDoc : public CDocument
{
protected: // create from serialization only
	CPC2PCDoc();
	DECLARE_DYNCREATE(CPC2PCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2PCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPC2PCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPC2PCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2PCDOC_H__87A631F8_763A_45FD_A98F_B86D8CA18232__INCLUDED_)
