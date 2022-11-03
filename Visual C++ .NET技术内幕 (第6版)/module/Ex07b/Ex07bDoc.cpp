// Ex07bDoc.cpp : implementation of the CEx07bDoc class
//

#include "stdafx.h"
#include "Ex07b.h"

#include "Ex07bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx07bDoc

IMPLEMENT_DYNCREATE(CEx07bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx07bDoc, CDocument)
END_MESSAGE_MAP()


// CEx07bDoc construction/destruction

CEx07bDoc::CEx07bDoc()
{
	// TODO: add one-time construction code here

}

CEx07bDoc::~CEx07bDoc()
{
}

BOOL CEx07bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx07bDoc serialization

void CEx07bDoc::Serialize(CArchive& ar)
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


// CEx07bDoc diagnostics

#ifdef _DEBUG
void CEx07bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx07bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx07bDoc commands
