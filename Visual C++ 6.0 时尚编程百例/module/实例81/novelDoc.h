// novelDoc.h : interface of the CNovelDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOVELDOC_H__68D9F56B_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_)
#define AFX_NOVELDOC_H__68D9F56B_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNovelDoc : public CDocument
{
protected: // create from serialization only
	CNovelDoc();
	DECLARE_DYNCREATE(CNovelDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNovelDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNovelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNovelDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOVELDOC_H__68D9F56B_B317_11D2_8B4D_00A0C92E6E9E__INCLUDED_)
