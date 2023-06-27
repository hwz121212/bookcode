#if !defined(AFX_THREADSERIAL_H__2644FDE3_FDF0_437A_BFBE_FB471DC99AAC__INCLUDED_)
#define AFX_THREADSERIAL_H__2644FDE3_FDF0_437A_BFBE_FB471DC99AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreadCom.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThreadCom thread

class CThreadCom : public CWinThread
{
	DECLARE_DYNCREATE(CThreadCom)
protected:
           // protected constructor used by dynamic creation

// Attributes
public:
	CThreadCom(HANDLE hCom=INVALID_HANDLE_VALUE);

// Operations
public:
	BOOL m_bOpen;
	
	BOOL SendData(LPCTSTR sBuf, DWORD dwLen);
	BOOL ReceiveData(LPCTSTR rBuf, int nMaxLength);
	BOOL OpenCom(CString com, DCB dcb,CWnd *pWndData,DWORD dwMsgToWndData,CWnd *pWndParent=NULL,DWORD dwMsgToParent=0);
	CString m_sError;
	BOOL m_bDone;
	CString m_Com;
	
	COMMTIMEOUTS m_Commtimeout;
	HANDLE GetComHandle();
	OVERLAPPED m_overWrite;
	OVERLAPPED m_overRead;
	BOOL CloseCom();
	
	virtual ~CThreadCom();
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadCom)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CThreadCom)
		// NOTE - the ClassWizard will add and remove member functions here.
	
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:	
	
	DWORD m_dwMsgToParent;
	DWORD m_dwMsgToData;
	CWnd* m_pWndData;
	CWnd* m_pWndParent;
	HANDLE m_hCom;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREADSERIAL_H__2644FDE3_FDF0_437A_BFBE_FB471DC99AAC__INCLUDED_)
