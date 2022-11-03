// PropSheetDoc.h : interface of the CPropSheetDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPSHEETDOC_H__682A1ECA_1396_11D4_A927_00001A012804__INCLUDED_)
#define AFX_PROPSHEETDOC_H__682A1ECA_1396_11D4_A927_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPropSheetDoc : public CDocument
{
protected: // create from serialization only
	CPropSheetDoc();
	DECLARE_DYNCREATE(CPropSheetDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropSheetDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropSheetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPropSheetDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPSHEETDOC_H__682A1ECA_1396_11D4_A927_00001A012804__INCLUDED_)
