// Print1View.h : interface of the CPrint1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINT1VIEW_H__DC72DC30_29C8_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_PRINT1VIEW_H__DC72DC30_29C8_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrint1View : public CScrollView
{
protected: // create from serialization only
	CPrint1View();
	DECLARE_DYNCREATE(CPrint1View)

// Attributes
public:
	CPrint1Doc* GetDocument();

// Operations
public:
private:
	CRect m_rectPrint;//可打印区域矩形 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrint1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrint1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrint1View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Print1View.cpp
inline CPrint1Doc* CPrint1View::GetDocument()
   { return (CPrint1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINT1VIEW_H__DC72DC30_29C8_11D4_9E64_00001A012804__INCLUDED_)
