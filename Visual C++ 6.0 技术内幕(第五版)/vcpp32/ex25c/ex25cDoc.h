// ex25cDoc.h : interface of the CEx25cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25cDOC_H__A9515B0C_5B85_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX25cDOC_H__A9515B0C_5B85_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx25cDoc : public CDocument
{
public:
	CString m_strFigure[4];
	CAlarm* m_pAlarm;
protected: // create from serialization only
	CEx25cDoc();
	DECLARE_DYNCREATE(CEx25cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx25cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx25cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CEx25cDoc)
	DATE m_time;
	afx_msg void OnTimeChanged();
	afx_msg void ShowWin();
	afx_msg LPDISPATCH CreateAlarm(DATE time);
	afx_msg void Refresh();
	afx_msg VARIANT GetFigure(short n);
	afx_msg void SetFigure(short n, const VARIANT FAR& newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25cDOC_H__A9515B0C_5B85_11D0_848F_00400526305B__INCLUDED_)
