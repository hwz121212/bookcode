// Print1Doc.h : interface of the CPrint1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINT1DOC_H__DC72DC2E_29C8_11D4_9E64_00001A012804__INCLUDED_)
#define AFX_PRINT1DOC_H__DC72DC2E_29C8_11D4_9E64_00001A012804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrint1Doc : public CDocument
{
protected: // create from serialization only
	CPrint1Doc();
	DECLARE_DYNCREATE(CPrint1Doc)

// Attributes
public:
       CStringArray m_StringArray;//保存文档数据
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrint1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrint1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrint1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINT1DOC_H__DC72DC2E_29C8_11D4_9E64_00001A012804__INCLUDED_)
