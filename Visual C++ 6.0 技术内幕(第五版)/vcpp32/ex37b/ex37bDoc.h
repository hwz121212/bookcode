// ex37bDoc.h : interface of the CEx37bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX37BDOC_H__97DB1277_0651_11D2_8524_444553540000__INCLUDED_)
#define AFX_EX37BDOC_H__97DB1277_0651_11D2_8524_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx37bDoc : public CDocument
{
protected: // create from serialization only
	CEx37bDoc();
	DECLARE_DYNCREATE(CEx37bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx37bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx37bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx37bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX37BDOC_H__97DB1277_0651_11D2_8524_444553540000__INCLUDED_)
