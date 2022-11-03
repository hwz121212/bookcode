// StatusDoc.h : interface of the CStatusDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSDOC_H__0372354A_1C1E_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_STATUSDOC_H__0372354A_1C1E_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStatusDoc : public CDocument
{
protected: // create from serialization only
	CStatusDoc();
	DECLARE_DYNCREATE(CStatusDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSDOC_H__0372354A_1C1E_11D4_B0E6_00001A012804__INCLUDED_)
