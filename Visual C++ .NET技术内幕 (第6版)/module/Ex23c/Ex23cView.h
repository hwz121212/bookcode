// Ex23cView.h : interface of the CEx23cView class
//


#pragma once


class CEx23cView : public CView
{
private:
   static const int nX[60];
   static const int nY[60];
   CFont m_font;

protected: // create from serialization only
	CEx23cView();
	DECLARE_DYNCREATE(CEx23cView)

// Attributes
public:
	CEx23cDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CEx23cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in Ex23cView.cpp
inline CEx23cDoc* CEx23cView::GetDocument() const
   { return reinterpret_cast<CEx23cDoc*>(m_pDocument); }
#endif

