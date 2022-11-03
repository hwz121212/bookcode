// Ex11bDoc.cpp : implementation of the CEx11bDoc class
//

#include "stdafx.h"
#include "Ex11b.h"

#include "Ex11bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx11bDoc

IMPLEMENT_DYNCREATE(CEx11bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx11bDoc, CDocument)
END_MESSAGE_MAP()


// CEx11bDoc construction/destruction

CEx11bDoc::CEx11bDoc()
{
	// TODO: add one-time construction code here

}

CEx11bDoc::~CEx11bDoc()
{
}

BOOL CEx11bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx11bDoc serialization

void CEx11bDoc::Serialize(CArchive& ar)
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


// CEx11bDoc diagnostics

#ifdef _DEBUG
void CEx11bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx11bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx11bDoc commands
