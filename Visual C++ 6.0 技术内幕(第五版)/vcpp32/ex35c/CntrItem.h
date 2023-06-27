// CntrItem.h : interface of the CEx35cCntrItem class
//

#if !defined(AFX_CNTRITEM_H__496552FF_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
#define AFX_CNTRITEM_H__496552FF_957C_11D0_85C0_97AC5D47DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx35cDoc;
class CEx35cView;

class CEx35cCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CEx35cCntrItem)

// Constructors
public:
	CEx35cCntrItem(REOBJECT* preo = NULL, CEx35cDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CEx35cDoc* GetDocument()
		{ return (CEx35cDoc*)CRichEditCntrItem::GetDocument(); }
	CEx35cView* GetActiveView()
		{ return (CEx35cView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx35cCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx35cCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__496552FF_957C_11D0_85C0_97AC5D47DD70__INCLUDED_)
