// ex25cView.h : interface of the CEx25cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25cVIEW_H__A9515B0E_5B85_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX25cVIEW_H__A9515B0E_5B85_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx25cView : public CView
{
private:
   static const int nX[60];
   static const int nY[60];
   CFont m_font;
protected: // create from serialization only
   CEx25cView();
   DECLARE_DYNCREATE(CEx25cView)

// Attributes
public:
   CEx25cDoc* GetDocument();

// Operations
public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CEx25cView)
   public:
   virtual void OnDraw(CDC* pDC);  // overridden to draw this view
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   //}}AFX_VIRTUAL

// Implementation
public:
   virtual ~CEx25cView();
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
   //{{AFX_MSG(CEx25cView)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex25cView.cpp
inline CEx25cDoc* CEx25cView::GetDocument()
   { return (CEx25cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25cVIEW_H__A9515B0E_5B85_11D0_848F_00400526305B__INCLUDED_)
