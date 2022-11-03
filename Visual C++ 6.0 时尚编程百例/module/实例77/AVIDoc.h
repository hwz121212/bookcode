// AVIDoc.h : interface of the CAVIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVIDOC_H__62F221EA_1F4F_11D4_B0E6_00001A012804__INCLUDED_)
#define AFX_AVIDOC_H__62F221EA_1F4F_11D4_B0E6_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAVIDoc : public CDocument
{
protected: // create from serialization only
	CAVIDoc();
	DECLARE_DYNCREATE(CAVIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAVIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAVIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIDOC_H__62F221EA_1F4F_11D4_B0E6_00001A012804__INCLUDED_)
