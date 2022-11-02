/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 管道编程－本地CMD.

  Project: ntLocalCmd.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntLocalCmdView.h : interface of the CNtLocalCmdView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NTLOCALCMDVIEW_H__5AAEC7DF_E1BF_4D54_A0FB_0955558FDB61__INCLUDED_)
#define AFX_NTLOCALCMDVIEW_H__5AAEC7DF_E1BF_4D54_A0FB_0955558FDB61__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CmdView.h"

class CNtLocalCmdView : public CCmdView
{
protected: // create from serialization only
	CNtLocalCmdView();
	DECLARE_DYNCREATE(CNtLocalCmdView)

// Attributes
public:
	CNtLocalCmdDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNtLocalCmdView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNtLocalCmdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNtLocalCmdView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ntLocalCmdView.cpp
inline CNtLocalCmdDoc* CNtLocalCmdView::GetDocument()
   { return (CNtLocalCmdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTLOCALCMDVIEW_H__5AAEC7DF_E1BF_4D54_A0FB_0955558FDB61__INCLUDED_)
