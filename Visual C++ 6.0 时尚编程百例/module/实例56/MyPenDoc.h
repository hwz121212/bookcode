// MyPenDoc.h : interface of the CMyPenDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPENDOC_H__BD6FCC8E_CD89_11D2_A71D_F9904D517C61__INCLUDED_)
#define AFX_MYPENDOC_H__BD6FCC8E_CD89_11D2_A71D_F9904D517C61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyPenDoc : public CDocument
{
protected: // create from serialization only
	CMyPenDoc();
	DECLARE_DYNCREATE(CMyPenDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyPenDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPENDOC_H__BD6FCC8E_CD89_11D2_A71D_F9904D517C61__INCLUDED_)
