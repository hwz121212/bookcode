#if !defined(AFX_REQUEST_H__55800FB6_28B3_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_REQUEST_H__55800FB6_28B3_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Request.h : header file
//

class CMainFrame;

/////////////////////////////////////////////////////////////////////////////
// CRequest command target

class CRequest : public CSocket
{
// Attributes
public:
	CMainFrame *m_pMainFrame;

// Operations
public:
	CRequest(CMainFrame *pMainFrame);
	virtual ~CRequest();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRequest)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRequest)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REQUEST_H__55800FB6_28B3_11D4_9E64_00001A012804__INCLUDED_)
