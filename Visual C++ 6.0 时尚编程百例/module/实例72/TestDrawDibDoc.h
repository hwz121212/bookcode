// TestDrawDibDoc.h : interface of the CTestDrawDibDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CTestDrawDibDoc : public CDocument
{
protected: // create from serialization only
	CTestDrawDibDoc();
	DECLARE_DYNCREATE(CTestDrawDibDoc)

// Attributes
public:
	HANDLE m_Buf;
	UINT m_Off;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDrawDibDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestDrawDibDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
// Generated message map functions
protected:
	//{{AFX_MSG(CTestDrawDibDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
