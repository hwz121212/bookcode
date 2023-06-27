// PC2PLCDoc.h : interface of the CPC2PLCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PC2PLCDOC_H__AA6A35AD_0F4C_4176_BA03_2B94C33511A9__INCLUDED_)
#define AFX_PC2PLCDOC_H__AA6A35AD_0F4C_4176_BA03_2B94C33511A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPC2PLCDoc : public CDocument
{
protected: // create from serialization only
	CPC2PLCDoc();
	DECLARE_DYNCREATE(CPC2PLCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPC2PLCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPC2PLCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPC2PLCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PC2PLCDOC_H__AA6A35AD_0F4C_4176_BA03_2B94C33511A9__INCLUDED_)
