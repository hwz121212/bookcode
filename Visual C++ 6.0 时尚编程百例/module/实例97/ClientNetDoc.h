// ClientNetDoc.h : interface of the CClientNetDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTNETDOC_H__55800FAA_28B3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_CLIENTNETDOC_H__55800FAA_28B3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClientNetDoc : public CDocument
{
protected: // create from serialization only
	CClientNetDoc();
	DECLARE_DYNCREATE(CClientNetDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientNetDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClientNetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientNetDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTNETDOC_H__55800FAA_28B3_11D4_9E64_00001A012804__INCLUDED_)
