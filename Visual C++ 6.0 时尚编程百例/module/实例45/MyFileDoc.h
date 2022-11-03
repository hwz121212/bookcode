// MyFileDoc.h : interface of the CMyFileDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFILEDOC_H__5862DF1F_DB10_11D2_A71D_B295A824025F__INCLUDED_)
#define AFX_MYFILEDOC_H__5862DF1F_DB10_11D2_A71D_B295A824025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyFileDoc : public CDocument
{
protected: // create from serialization only
	CMyFileDoc();
	DECLARE_DYNCREATE(CMyFileDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFileDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyFileDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFileDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFILEDOC_H__5862DF1F_DB10_11D2_A71D_B295A824025F__INCLUDED_)
