// ex25eDoc.h : interface of the CEx25eDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25eDOC_H__F02781AB_6269_11D0_8490_00400526305B__INCLUDED_)
#define AFX_EX25eDOC_H__F02781AB_6269_11D0_8490_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx25eDoc : public CDocument
{
protected: // create from serialization only
	CEx25eDoc();
	DECLARE_DYNCREATE(CEx25eDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25eDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx25eDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx25eDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25eDOC_H__F02781AB_6269_11D0_8490_00400526305B__INCLUDED_)
