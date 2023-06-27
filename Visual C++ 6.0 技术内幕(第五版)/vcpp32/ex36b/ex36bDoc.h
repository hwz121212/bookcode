// ex36bDoc.h : interface of the CEx36bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx36bSrvrItem;

class CEx36bDoc : public COleServerDoc
{
public:
	int		m_nPeriod;
protected: // create from serialization only
	CEx36bDoc();
	DECLARE_DYNCREATE(CEx36bDoc)

// Attributes
public:
	CEx36bSrvrItem* GetEmbeddedItem()
		{ return (CEx36bSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx36bDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx36bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx36bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
