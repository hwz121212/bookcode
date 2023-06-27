// ex14cDoc.h : interface of the CEx14cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX14CDOC_H__C7C8580B_E3B0_11D1_8524_A6295F36C950__INCLUDED_)
#define AFX_EX14CDOC_H__C7C8580B_E3B0_11D1_8524_A6295F36C950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx14cDoc : public CDocument
{
protected: // create from serialization only
	CEx14cDoc();
	DECLARE_DYNCREATE(CEx14cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx14cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx14cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14CDOC_H__C7C8580B_E3B0_11D1_8524_A6295F36C950__INCLUDED_)
