// SrvrItem.h : interface of the CEx36bSrvrItem class
//

class CEx36bSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CEx36bSrvrItem)

// Constructors
public:
	CEx36bSrvrItem(CEx36bDoc* pContainerDoc);

// Attributes
	CEx36bDoc* GetDocument() const
		{ return (CEx36bDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx36bSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx36bSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
