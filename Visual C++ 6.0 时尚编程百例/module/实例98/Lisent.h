#if !defined(AFX_LISENT_H__ED9EBC77_2907_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_LISENT_H__ED9EBC77_2907_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lisent.h : header file
//


class CMainFrame;
/////////////////////////////////////////////////////////////////////////////
// CLisent command target

class CLisent : public CSocket
{
// Attributes
public:
	CMainFrame *m_pMainFrame;

// Operations
public:
	CLisent(CMainFrame *pMainFrame);
	virtual ~CLisent();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLisent)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLisent)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISENT_H__ED9EBC77_2907_11D4_9E64_00001A012804__INCLUDED_)
