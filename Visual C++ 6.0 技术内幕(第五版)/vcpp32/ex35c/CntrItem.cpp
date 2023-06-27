// CntrItem.cpp : implementation of the CEx35cCntrItem class
//

#include "stdafx.h"
#include "ex35c.h"

#include "ex35cDoc.h"
#include "ex35cView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx35cCntrItem implementation

IMPLEMENT_SERIAL(CEx35cCntrItem, CRichEditCntrItem, 0)

CEx35cCntrItem::CEx35cCntrItem(REOBJECT* preo, CEx35cDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CEx35cCntrItem::~CEx35cCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CEx35cCntrItem diagnostics

#ifdef _DEBUG
void CEx35cCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEx35cCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
