// KeyScrollDoc.h : interface of the CKeyScrollDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYSCROLLDOC_H__E07A232C_3998_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_KEYSCROLLDOC_H__E07A232C_3998_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKeyScrollDoc : public CDocument
{
protected: // create from serialization only
	CKeyScrollDoc();
	DECLARE_DYNCREATE(CKeyScrollDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyScrollDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKeyScrollDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKeyScrollDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYSCROLLDOC_H__E07A232C_3998_11D4_9E64_00001A012804__INCLUDED_)
