// ClientNetView.h : interface of the CClientNetView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTNETVIEW_H__55800FAC_28B3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_CLIENTNETVIEW_H__55800FAC_28B3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClientNetView : public CView
{
protected: // create from serialization only
	CClientNetView();
	DECLARE_DYNCREATE(CClientNetView)

// Attributes
public:
	CClientNetDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientNetView)
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
	virtual ~CClientNetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientNetView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ClientNetView.cpp
inline CClientNetDoc* CClientNetView::GetDocument()
   { return (CClientNetDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTNETVIEW_H__55800FAC_28B3_11D4_9E64_00001A012804__INCLUDED_)
