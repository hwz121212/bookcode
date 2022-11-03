// Print2Doc.h : interface of the CPrint2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINT2DOC_H__7DC5A74A_2B15_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_PRINT2DOC_H__7DC5A74A_2B15_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef CArray<CRect,CRect&> CRectArray;//
class CPrint2Doc : public CDocument
{
protected: // create from serialization only
	CPrint2Doc();
	DECLARE_DYNCREATE(CPrint2Doc)

// Attributes
public:
	enum{nLinesPage=12};
	enum{nMaxRect=50};
    CRectArray m_rectArray;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrint2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrint2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrint2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINT2DOC_H__7DC5A74A_2B15_11D4_9E64_00001A012804__INCLUDED_)
