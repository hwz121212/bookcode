// ServerNetDoc.h : interface of the CServerNetDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERNETDOC_H__ED9EBC6C_2907_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_SERVERNETDOC_H__ED9EBC6C_2907_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CServerNetDoc : public CDocument
{
protected: // create from serialization only
	CServerNetDoc();
	DECLARE_DYNCREATE(CServerNetDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerNetDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CServerNetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CServerNetDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERNETDOC_H__ED9EBC6C_2907_11D4_9E64_00001A012804__INCLUDED_)
