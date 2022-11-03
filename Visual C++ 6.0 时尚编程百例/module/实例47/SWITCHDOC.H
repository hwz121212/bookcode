// switchDoc.h : interface of the CSwitchDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWITCHDOC_H__B21A70FA_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
#define AFX_SWITCHDOC_H__B21A70FA_7F31_11D2_BE4E_0000216A06C9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSwitchDoc : public CDocument
{
protected: // create from serialization only
	CSwitchDoc();
	DECLARE_DYNCREATE(CSwitchDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwitchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHDOC_H__B21A70FA_7F31_11D2_BE4E_0000216A06C9__INCLUDED_)
