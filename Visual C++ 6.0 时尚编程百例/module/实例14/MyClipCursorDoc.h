// MyClipCursorDoc.h : interface of the CMyClipCursorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLIPCURSORDOC_H__BF47E8CB_114A_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYCLIPCURSORDOC_H__BF47E8CB_114A_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyClipCursorDoc : public CDocument
{
protected: // create from serialization only
	CMyClipCursorDoc();
	DECLARE_DYNCREATE(CMyClipCursorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClipCursorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyClipCursorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyClipCursorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLIPCURSORDOC_H__BF47E8CB_114A_11D4_876D_00001CD613F0__INCLUDED_)
