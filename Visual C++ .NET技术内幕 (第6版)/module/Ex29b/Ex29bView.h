// Ex29bView.h : interface of the CEx29bView class
//


#pragma once


class CEx29bView : public CHtmlView
{
protected: // create from serialization only
	CEx29bView();
	DECLARE_DYNCREATE(CEx29bView)

// Attributes
public:
	CEx29bDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CEx29bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex29bView.cpp
inline CEx29bDoc* CEx29bView::GetDocument() const
   { return reinterpret_cast<CEx29bDoc*>(m_pDocument); }
#endif

