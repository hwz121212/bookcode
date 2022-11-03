// MySerializeDoc.h : interface of the CMySerializeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSERIALIZEDOC_H__DFC8F82B_10B2_11D4_876D_00001CD613F0__INCLUDED_)
#define AFX_MYSERIALIZEDOC_H__DFC8F82B_10B2_11D4_876D_00001CD613F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMySerializeDoc : public CDocument
{
protected: // create from serialization only
	CMySerializeDoc();
	DECLARE_DYNCREATE(CMySerializeDoc)

// Attributes
public:
	CString StrName;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySerializeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMySerializeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMySerializeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERIALIZEDOC_H__DFC8F82B_10B2_11D4_876D_00001CD613F0__INCLUDED_)
