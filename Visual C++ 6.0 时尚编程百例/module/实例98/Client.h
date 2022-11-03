#if !defined(AFX_CLIENT_H__ED9EBC78_2907_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_CLIENT_H__ED9EBC78_2907_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Client.h : header file
//

class CMainFrame;

/////////////////////////////////////////////////////////////////////////////
// CClient command target

class CClient : public CSocket
{
// Attributes
public:
      CMainFrame *m_pMainFrame;
// Operations
public:
	CClient(CMainFrame *pMainFrame);
	virtual ~CClient();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClient)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_H__ED9EBC78_2907_11D4_9E64_00001A012804__INCLUDED_)
