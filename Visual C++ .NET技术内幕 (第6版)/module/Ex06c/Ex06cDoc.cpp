// Ex06cDoc.cpp : implementation of the CEx06cDoc class
//

#include "stdafx.h"
#include "Ex06c.h"

#include "Ex06cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06cDoc

IMPLEMENT_DYNCREATE(CEx06cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx06cDoc, CDocument)
END_MESSAGE_MAP()


// CEx06cDoc construction/destruction

CEx06cDoc::CEx06cDoc()
{
	// TODO: add one-time construction code here

}

CEx06cDoc::~CEx06cDoc()
{
}

BOOL CEx06cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx06cDoc serialization

void CEx06cDoc::Serialize(CArchive& ar)
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


// CEx06cDoc diagnostics

#ifdef _DEBUG
void CEx06cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx06cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx06cDoc commands
