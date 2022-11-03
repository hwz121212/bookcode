// MySplitterDoc.h : interface of the CMySplitterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSPLITTERDOC_H__ABADB26B_1120_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYSPLITTERDOC_H__ABADB26B_1120_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMySplitterDoc : public CDocument
{
protected: // create from serialization only
	CMySplitterDoc();
	DECLARE_DYNCREATE(CMySplitterDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySplitterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMySplitterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMySplitterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPLITTERDOC_H__ABADB26B_1120_11D4_876D_00001CD613F0__INCLUDED_)
