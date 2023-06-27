#ifndef __EX25BAUTO_H__
#define __EX25BAUTO_H__

// Ex25bAuto.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CEx25bAuto command target

class CEx25bAuto : public CCmdTarget
{
	DECLARE_DYNCREATE(CEx25bAuto)

	CEx25bAuto();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25bAuto)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEx25bAuto();

	// Generated message map functions
	//{{AFX_MSG(CEx25bAuto)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CEx25bAuto)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CEx25bAuto)
	long m_lData;
	afx_msg void OnLongDataChanged();
	VARIANT m_vaTextData;
	afx_msg void OnTextDataChanged();
	afx_msg BOOL DisplayDialog();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __EX25bAUTO_H__
