// MyScrollDoc.h : interface of the CMyScrollDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSCROLLDOC_H__88511F0D_B947_11D2_A71D_EEA983D5DD6C__INCLUDED_)
#define AFX_MYSCROLLDOC_H__88511F0D_B947_11D2_A71D_EEA983D5DD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyScrollDoc : public CDocument
{
protected: // create from serialization only
	CMyScrollDoc();
	DECLARE_DYNCREATE(CMyScrollDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyScrollDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyScrollDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyScrollDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSCROLLDOC_H__88511F0D_B947_11D2_A71D_EEA983D5DD6C__INCLUDED_)
