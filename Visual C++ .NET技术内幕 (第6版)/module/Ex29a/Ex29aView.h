// Ex29aView.h : interface of the CEx29aView class
//


#pragma once


class CEx29aView : public CHtmlView
{
protected: // create from serialization only
	CEx29aView();
	DECLARE_DYNCREATE(CEx29aView)

// Attributes
public:
	CEx29aDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CEx29aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex29aView.cpp
inline CEx29aDoc* CEx29aView::GetDocument() const
   { return reinterpret_cast<CEx29aDoc*>(m_pDocument); }
#endif

