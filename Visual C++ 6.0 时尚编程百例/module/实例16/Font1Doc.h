// Font1Doc.h : interface of the CFont1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONT1DOC_H__BAE6D14A_12FA_11D4_A927_00001A012804__INCLUDED_)
#define AFX_FONT1DOC_H__BAE6D14A_12FA_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFont1Doc : public CDocument
{
protected: // create from serialization only
	CFont1Doc();
	DECLARE_DYNCREATE(CFont1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFont1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFont1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFont1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONT1DOC_H__BAE6D14A_12FA_11D4_A927_00001A012804__INCLUDED_)
