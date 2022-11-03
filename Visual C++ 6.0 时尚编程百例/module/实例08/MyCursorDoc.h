// MyCursorDoc.h : interface of the CMyCursorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCURSORDOC_H__3C96996B_0F2B_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYCURSORDOC_H__3C96996B_0F2B_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyCursorDoc : public CDocument
{
protected: // create from serialization only
	CMyCursorDoc();
	DECLARE_DYNCREATE(CMyCursorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCursorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyCursorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCursorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCURSORDOC_H__3C96996B_0F2B_11D4_876D_00001CD613F0__INCLUDED_)
