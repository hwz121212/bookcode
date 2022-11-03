// TimerDoc.h : interface of the CTimerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMERDOC_H__1E490D1B_E392_11D2_A71D_924A9FFD7F4B__INCLUDED_)
#define AFX_TIMERDOC_H__1E490D1B_E392_11D2_A71D_924A9FFD7F4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTimerDoc : public CDocument
{
protected: // create from serialization only
	CTimerDoc();
	DECLARE_DYNCREATE(CTimerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTimerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTimerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDOC_H__1E490D1B_E392_11D2_A71D_924A9FFD7F4B__INCLUDED_)
