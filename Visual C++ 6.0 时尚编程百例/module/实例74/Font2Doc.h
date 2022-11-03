// Font2Doc.h : interface of the CFont2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONT2DOC_H__BAE6D15E_12FA_11D4_A927_00001A012804__INCLUDED_)
#define AFX_FONT2DOC_H__BAE6D15E_12FA_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFont2Doc : public CDocument
{
protected: // create from serialization only
	CFont2Doc();
	DECLARE_DYNCREATE(CFont2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFont2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFont2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFont2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONT2DOC_H__BAE6D15E_12FA_11D4_A927_00001A012804__INCLUDED_)
