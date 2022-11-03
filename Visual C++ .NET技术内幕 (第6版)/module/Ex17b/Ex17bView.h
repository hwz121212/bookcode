// Ex17bView.h : interface of the CEx17bView class
//


#pragma once


class CEx17bView : public CView
{
protected: // create from serialization only
	CEx17bView();
	DECLARE_DYNCREATE(CEx17bView)

// Attributes
public:
	CEx17bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEx17bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_nPage;
private:
	void PrintPageHeader(CDC *pDC);
	void PrintPageFooter(CDC *pDC);
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
};

#ifndef _DEBUG  // debug version in Ex17bView.cpp
inline CEx17bDoc* CEx17bView::GetDocument() const
   { return reinterpret_cast<CEx17bDoc*>(m_pDocument); }
#endif

