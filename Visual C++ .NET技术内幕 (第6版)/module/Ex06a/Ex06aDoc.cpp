// Ex06aDoc.cpp : implementation of the CEx06aDoc class
//

#include "stdafx.h"
#include "Ex06a.h"

#include "Ex06aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06aDoc

IMPLEMENT_DYNCREATE(CEx06aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx06aDoc, CDocument)
END_MESSAGE_MAP()


// CEx06aDoc construction/destruction

CEx06aDoc::CEx06aDoc()
{
	// TODO: add one-time construction code here

}

CEx06aDoc::~CEx06aDoc()
{
}

BOOL CEx06aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx06aDoc serialization

void CEx06aDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CEx06aDoc diagnostics

#ifdef _DEBUG
void CEx06aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx06aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx06aDoc commands
