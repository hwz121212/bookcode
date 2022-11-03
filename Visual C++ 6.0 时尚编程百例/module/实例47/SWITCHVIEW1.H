#if !defined(AFX_SWITCHVIEW1_H__B21A7105_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
#define AFX_SWITCHVIEW1_H__B21A7105_7F31_11D2_BE4E_0000216A06C9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SwitchView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSwitchView1 view

class CSwitchView1 : public CView
{
protected:
	CSwitchView1();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSwitchView1)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchView1)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSwitchView1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchView1)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHVIEW1_H__B21A7105_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
