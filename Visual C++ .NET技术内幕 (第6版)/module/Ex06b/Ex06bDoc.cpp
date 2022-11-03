// Ex06bDoc.cpp : implementation of the CEx06bDoc class
//

#include "stdafx.h"
#include "Ex06b.h"

#include "Ex06bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06bDoc

IMPLEMENT_DYNCREATE(CEx06bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx06bDoc, CDocument)
END_MESSAGE_MAP()


// CEx06bDoc construction/destruction

CEx06bDoc::CEx06bDoc()
{
	// TODO: add one-time construction code here

}

CEx06bDoc::~CEx06bDoc()
{
}

BOOL CEx06bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx06bDoc serialization

void CEx06bDoc::Serialize(CArchive& ar)
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


// CEx06bDoc diagnostics

#ifdef _DEBUG
void CEx06bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx06bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx06bDoc commands
