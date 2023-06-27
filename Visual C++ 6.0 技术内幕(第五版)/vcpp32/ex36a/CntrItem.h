// CntrItem.h : interface of the CEx36aCntrItem class
//

class CEx36aDoc;
class CEx36aView;

class CEx36aCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CEx36aCntrItem)

// Constructors
public:
	CEx36aCntrItem(REOBJECT* preo = NULL, CEx36aDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CEx36aDoc* GetDocument()
		{ return (CEx36aDoc*)CRichEditCntrItem::GetDocument(); }
	CEx36aView* GetActiveView()
		{ return (CEx36aView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx36aCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx36aCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
