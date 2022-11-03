// AnimateDoc.h : interface of the CAnimateDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMATEDOC_H__C28396CA_1D06_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_ANIMATEDOC_H__C28396CA_1D06_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAnimateDoc : public CDocument
{
protected: // create from serialization only
	CAnimateDoc();
	DECLARE_DYNCREATE(CAnimateDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimateDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnimateDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEDOC_H__C28396CA_1D06_11D4_B0E6_00001A012804__INCLUDED_)
