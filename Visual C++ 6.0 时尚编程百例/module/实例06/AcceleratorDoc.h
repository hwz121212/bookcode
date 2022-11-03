// AcceleratorDoc.h : interface of the CAcceleratorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCELERATORDOC_H__72E9986B_B87D_11D2_A71D_CAEB1B5C016B__INCLUDED_)
#define AFX_ACCELERATORDOC_H__72E9986B_B87D_11D2_A71D_CAEB1B5C016B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAcceleratorDoc : public CDocument
{
protected: // create from serialization only
	CAcceleratorDoc();
	DECLARE_DYNCREATE(CAcceleratorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcceleratorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAcceleratorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAcceleratorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCELERATORDOC_H__72E9986B_B87D_11D2_A71D_CAEB1B5C016B__INCLUDED_)
