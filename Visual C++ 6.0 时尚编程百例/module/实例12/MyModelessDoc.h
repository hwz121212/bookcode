// MyModelessDoc.h : interface of the CMyModelessDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMODELESSDOC_H__33D4FC3F_C0DC_11D2_A71D_9648DA4D456A__INCLUDED_)
#define AFX_MYMODELESSDOC_H__33D4FC3F_C0DC_11D2_A71D_9648DA4D456A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyModelessDoc : public CDocument
{
protected: // create from serialization only
	CMyModelessDoc();
	DECLARE_DYNCREATE(CMyModelessDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyModelessDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyModelessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyModelessDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMODELESSDOC_H__33D4FC3F_C0DC_11D2_A71D_9648DA4D456A__INCLUDED_)
