// GetMemoryDoc.h : interface of the CGetMemoryDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETMEMORYDOC_H__B14DE13F_C5FB_11D2_A71D_F2A73EE8E169__INCLUDED_)
#define AFX_GETMEMORYDOC_H__B14DE13F_C5FB_11D2_A71D_F2A73EE8E169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGetMemoryDoc : public CDocument
{
protected: // create from serialization only
	CGetMemoryDoc();
	DECLARE_DYNCREATE(CGetMemoryDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetMemoryDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGetMemoryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGetMemoryDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETMEMORYDOC_H__B14DE13F_C5FB_11D2_A71D_F2A73EE8E169__INCLUDED_)
