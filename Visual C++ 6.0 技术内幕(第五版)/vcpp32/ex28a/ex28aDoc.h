// ex28aDoc.h : interface of the CEx28aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28ADOC_H__D4B8ACCC_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX28ADOC_H__D4B8ACCC_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx28aSrvrItem;

class CEx28aDoc : public COleServerDoc
{
public:
	CString m_strText;

protected: // create from serialization only
	CEx28aDoc();
	DECLARE_DYNCREATE(CEx28aDoc)

// Attributes
public:
	CEx28aSrvrItem* GetEmbeddedItem()
		{ return (CEx28aSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28aDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28aDoc)
	afx_msg void OnModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28ADOC_H__D4B8ACCC_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_)
