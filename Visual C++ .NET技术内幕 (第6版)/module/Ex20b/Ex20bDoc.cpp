// Ex20bDoc.cpp : implementation of the CEx20bDoc class
//

#include "stdafx.h"
#include "Ex20b.h"

#include "Ex20bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx20bDoc

IMPLEMENT_DYNCREATE(CEx20bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx20bDoc, CDocument)
END_MESSAGE_MAP()


// CEx20bDoc construction/destruction

CEx20bDoc::CEx20bDoc()
{
	// TODO: add one-time construction code here

}

CEx20bDoc::~CEx20bDoc()
{
}

BOOL CEx20bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx20bDoc serialization

void CEx20bDoc::Serialize(CArchive& ar)
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


// CEx20bDoc diagnostics

#ifdef _DEBUG
void CEx20bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx20bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx20bDoc commands
