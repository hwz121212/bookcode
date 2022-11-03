// CharviewDoc.h : interface of the CCharviewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARVIEWDOC_H__96F07F2A_1480_11D4_A927_00001A012804__INCLUDED_)
#define AFX_CHARVIEWDOC_H__96F07F2A_1480_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int MAX_LINES=1000;
class CCharviewDoc : public CDocument
{
protected: // create from serialization only
	CCharviewDoc();
	DECLARE_DYNCREATE(CCharviewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharviewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString Text[MAX_LINES];
	virtual ~CCharviewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
public:
 int number;
// Generated message map functions
protected:
	//{{AFX_MSG(CCharviewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARVIEWDOC_H__96F07F2A_1480_11D4_A927_00001A012804__INCLUDED_)
