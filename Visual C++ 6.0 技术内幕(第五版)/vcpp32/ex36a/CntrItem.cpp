// CntrItem.cpp : implementation of the CEx36aCntrItem class
//

#include "stdafx.h"
#include "ex36a.h"

#include "ex36aDoc.h"
#include "ex36aView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx36aCntrItem implementation

IMPLEMENT_SERIAL(CEx36aCntrItem, CRichEditCntrItem, 0)

CEx36aCntrItem::CEx36aCntrItem(REOBJECT* preo, CEx36aDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CEx36aCntrItem::~CEx36aCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CEx36aCntrItem diagnostics

#ifdef _DEBUG
void CEx36aCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEx36aCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
