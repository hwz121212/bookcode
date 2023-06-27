// SrvrItem.h : interface of the CEx28aSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__D4B8ACD1_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_)
#define AFX_SRVRITEM_H__D4B8ACD1_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEx28aSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CEx28aSrvrItem)

// Constructors
public:
	CEx28aSrvrItem(CEx28aDoc* pContainerDoc);

// Attributes
	CEx28aDoc* GetDocument() const
		{ return (CEx28aDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28aSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx28aSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__D4B8ACD1_FA2D_11D1_B30A_0080C7360DC1__INCLUDED_)
