// TTYSendApiDoc.h : interface of the CTTYSendApiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTYSENDAPIDOC_H__A0CB1F30_C320_4224_AD0D_761F124F9929__INCLUDED_)
#define AFX_TTYSENDAPIDOC_H__A0CB1F30_C320_4224_AD0D_761F124F9929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTTYSendApiDoc : public CDocument
{
protected: // create from serialization only
	CTTYSendApiDoc();
	DECLARE_DYNCREATE(CTTYSendApiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYSendApiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTTYSendApiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTTYSendApiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTYSENDAPIDOC_H__A0CB1F30_C320_4224_AD0D_761F124F9929__INCLUDED_)
