#if !defined(AFX_VIEWTREEGIS_H__A5EA22B9_CD2B_46B9_AD36_3D9B306AA30B__INCLUDED_)
#define AFX_VIEWTREEGIS_H__A5EA22B9_CD2B_46B9_AD36_3D9B306AA30B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewTreeCom.h : header file
//
#include "ComWorkFlow.h"

/////////////////////////////////////////////////////////////////////////////
// CViewTreeCom view

class CViewTreeCom : public CTreeView
{
protected:
	CViewTreeCom();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewTreeCom)

// Attributes
public:

// Operations
public:
	void DeleteCom(CComWorkFlow *obj);
	void InsertCom(CComWorkFlow *obj);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewTreeCom)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewTreeCom();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewTreeCom)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWTREEGIS_H__A5EA22B9_CD2B_46B9_AD36_3D9B306AA30B__INCLUDED_)
