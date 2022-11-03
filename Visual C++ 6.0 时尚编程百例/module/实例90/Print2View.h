// Print2View.h : interface of the CPrint2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINT2VIEW_H__7DC5A74C_2B15_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_PRINT2VIEW_H__7DC5A74C_2B15_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrint2View : public CView
{
protected: // create from serialization only
	CPrint2View();
	DECLARE_DYNCREATE(CPrint2View)

// Attributes
public:
	CPrint2Doc* GetDocument();

// Operations
public:
	int m_Page;
private:
	void PrintPageHead(CDC *pDC);
	void PrintPageFooter(CDC *pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrint2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrint2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrint2View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Print2View.cpp
inline CPrint2Doc* CPrint2View::GetDocument()
   { return (CPrint2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINT2VIEW_H__7DC5A74C_2B15_11D4_9E64_00001A012804__INCLUDED_)
