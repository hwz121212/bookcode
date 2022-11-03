// WavePlayView.h : interface of the CWavePlayView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEPLAYVIEW_H__FE23608D_C1AD_11D2_A71D_DB01F71B576A__INCLUDED_)
#define AFX_WAVEPLAYVIEW_H__FE23608D_C1AD_11D2_A71D_DB01F71B576A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wave.h"

class CWavePlayView : public CView
{
protected: // create from serialization only
	CWavePlayView();
	DECLARE_DYNCREATE(CWavePlayView)

// Attributes
public:
	CWavePlayDoc* GetDocument();

// Operations
public:
	CWave m_wave;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavePlayView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWavePlayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWavePlayView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WavePlayView.cpp
inline CWavePlayDoc* CWavePlayView::GetDocument()
   { return (CWavePlayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEPLAYVIEW_H__FE23608D_C1AD_11D2_A71D_DB01F71B576A__INCLUDED_)
