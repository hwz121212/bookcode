// Ex13bDoc.cpp : implementation of the CEx13bDoc class
//

#include "stdafx.h"
#include "Ex13b.h"

#include "Ex13bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx13bDoc

IMPLEMENT_DYNCREATE(CEx13bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx13bDoc, CDocument)
END_MESSAGE_MAP()


// CEx13bDoc construction/destruction

CEx13bDoc::CEx13bDoc()
{
	// TODO: add one-time construction code here

}

CEx13bDoc::~CEx13bDoc()
{
}

BOOL CEx13bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx13bDoc serialization

void CEx13bDoc::Serialize(CArchive& ar)
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


// CEx13bDoc diagnostics

#ifdef _DEBUG
void CEx13bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx13bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx13bDoc commands
