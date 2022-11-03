// ShowBmpDoc.h : interface of the CShowBmpDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWBMPDOC_H__958A28B2_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
#define AFX_SHOWBMPDOC_H__958A28B2_DB28_11D2_A71D_D12047679B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShowBmpDoc : public CDocument
{
protected: // create from serialization only
	CShowBmpDoc();
	DECLARE_DYNCREATE(CShowBmpDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowBmpDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowBmpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShowBmpDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWBMPDOC_H__958A28B2_DB28_11D2_A71D_D12047679B5A__INCLUDED_)
