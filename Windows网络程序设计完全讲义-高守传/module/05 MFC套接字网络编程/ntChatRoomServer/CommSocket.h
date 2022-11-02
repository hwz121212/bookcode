#if !defined(AFX_COMMSOCKET_H__6AB42DCF_93B5_48D0_A826_790B1AB7F7BE__INCLUDED_)
#define AFX_COMMSOCKET_H__6AB42DCF_93B5_48D0_A826_790B1AB7F7BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCommSocket command target
class CCommSocketList;
class CCommSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CCommSocket(CCommSocketList *);
	virtual ~CCommSocket();

// Overrides
public:

	CCommSocketList *List;
	CCommSocket * Front;
	CCommSocket * Next;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCommSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSOCKET_H__6AB42DCF_93B5_48D0_A826_790B1AB7F7BE__INCLUDED_)
