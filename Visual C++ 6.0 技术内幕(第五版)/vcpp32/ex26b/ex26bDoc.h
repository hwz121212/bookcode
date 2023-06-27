// ex26bDoc.h : interface of the CEx26bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26BDOC_H__4D1ED004_01E1_11D2_B30A_0080C7360DC1__INCLUDED_)
#define AFX_EX26BDOC_H__4D1ED004_01E1_11D2_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx26bDoc : public CDocument
{
public:
    CDib m_dib;
    BOOL m_bDragHere; // for drags between two wins linked to this doc
protected: // create from serialization only
	CEx26bDoc();
	DECLARE_DYNCREATE(CEx26bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	//{{AFX_MSG(CEx26bDoc)
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26BDOC_H__4D1ED004_01E1_11D2_B30A_0080C7360DC1__INCLUDED_)
