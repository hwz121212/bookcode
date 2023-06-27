// ex05aView.h : interface of the CEx05aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX05AVIEW_H__B6B0A0ED_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
#define AFX_EX05AVIEW_H__B6B0A0ED_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx05aView : public CView
{
protected: // create from serialization only
	CEx05aView();
	DECLARE_DYNCREATE(CEx05aView)

// Attributes
public:
	CEx05aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx05aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	//}}AFX_VIRTUAL

private:
    void ShowFont(CDC* pDC, int& nPos, int nPoints);

// Implementation
public:
	virtual ~CEx05aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx05aView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex05aView.cpp
inline CEx05aDoc* CEx05aView::GetDocument()
   { return (CEx05aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX05AVIEW_H__B6B0A0ED_9C84_11D1_8ED7_0080C7360DC1__INCLUDED_)
