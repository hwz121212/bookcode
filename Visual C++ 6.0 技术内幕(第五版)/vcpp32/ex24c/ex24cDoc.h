// ex24cDoc.h : interface of the CEx24cDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX24CDOC_H__4F329AF9_5DF1_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX24CDOC_H__4F329AF9_5DF1_11D0_848F_00400526305B__INCLUDED_


class CEx24cDoc : public CDocument
{
protected: // create from serialization only
	CEx24cDoc();
	DECLARE_DYNCREATE(CEx24cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx24cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx24cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx24cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX24CDOC_H__4F329AF9_5DF1_11D0_848F_00400526305B__INCLUDED_)
