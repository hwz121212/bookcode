// DrawBottunDoc.h : interface of the CDrawBottunDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBOTTUNDOC_H__4AF533EB_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
#define AFX_DRAWBOTTUNDOC_H__4AF533EB_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawBottunDoc : public CDocument
{
protected: // create from serialization only
	CDrawBottunDoc();
	DECLARE_DYNCREATE(CDrawBottunDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawBottunDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawBottunDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawBottunDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWBOTTUNDOC_H__4AF533EB_C125_11D2_A71D_A0815CB6AA6A__INCLUDED_)
