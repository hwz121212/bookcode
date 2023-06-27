#if !defined(AFX_VIEWCOMDATA_H__42CAA594_6A98_4468_8DB6_A1976FB25071__INCLUDED_)
#define AFX_VIEWCOMDATA_H__42CAA594_6A98_4468_8DB6_A1976FB25071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewComData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewComData form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CViewComData : public CFormView
{
protected:
	CViewComData();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewComData)

// Form Data
public:
	//{{AFX_DATA(CViewComData)
	enum { IDD = IDD_FORMVIEW_COM };
	CComboBox	m_comboType;
	CEdit	m_comEdit;
	CEdit	m_sendEdit;
	CEdit	m_receEdit;
	CString	m_Com;
	CString	m_sendData;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void InsertReceiveData(CString pSource, CString pData);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewComData)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewComData();

	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewComData)
	afx_msg void OnButtonSend();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnButtonAddtail();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCOMDATA_H__42CAA594_6A98_4468_8DB6_A1976FB25071__INCLUDED_)
