// SrvrItem.h : interface of the CEx36aSrvrItem class
//

class CEx36aSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CEx36aSrvrItem)

// Constructors
public:
	CEx36aSrvrItem(CEx36aDoc* pContainerDoc);

// Attributes
	CEx36aDoc* GetDocument() const
		{ return (CEx36aDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx36aSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx36aSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
