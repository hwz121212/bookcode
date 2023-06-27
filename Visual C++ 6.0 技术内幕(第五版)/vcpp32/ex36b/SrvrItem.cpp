// SrvrItem.cpp : implementation of the CEx36bSrvrItem class
//

#include "stdafx.h"
#include "ex36b.h"

#include "ex36bDoc.h"
#include "SrvrItem.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx36bSrvrItem implementation

IMPLEMENT_DYNAMIC(CEx36bSrvrItem, CDocObjectServerItem)

CEx36bSrvrItem::CEx36bSrvrItem(CEx36bDoc* pContainerDoc)
	: CDocObjectServerItem(pContainerDoc, TRUE)
{
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
}

CEx36bSrvrItem::~CEx36bSrvrItem()
{
	// TODO: add cleanup code here
}

void CEx36bSrvrItem::Serialize(CArchive& ar)
{
	// CEx36bSrvrItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.

	if (!IsLinkedItem())
	{
		CEx36bDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

BOOL CEx36bSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

	if (dwDrawAspect != DVASPECT_CONTENT)
		return CDocObjectServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CEx36bSrvrItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	CEx36bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: replace this arbitrary size

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC units

	return TRUE;
}

BOOL CEx36bSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	CEx36bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: add drawing code here.  Optionally, fill in the HIMETRIC extent.
	//  All drawing takes place in the metafile device context (pDC).

	// TODO: also draw embedded CEx36bCntrItem objects.

	// The following code draws the first item at an arbitrary position.

	// TODO: remove this code when your real drawing code is complete

	POSITION pos = pDoc->GetStartPosition();
	CEx36bCntrItem* pItem = (CEx36bCntrItem*)pDoc->GetNextClientItem(pos);
	if (pItem != NULL)
		pItem->Draw(pDC, CRect(10, 10, 1010, 1010));
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx36bSrvrItem diagnostics

#ifdef _DEBUG
void CEx36bSrvrItem::AssertValid() const
{
	CDocObjectServerItem::AssertValid();
}

void CEx36bSrvrItem::Dump(CDumpContext& dc) const
{
	CDocObjectServerItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
