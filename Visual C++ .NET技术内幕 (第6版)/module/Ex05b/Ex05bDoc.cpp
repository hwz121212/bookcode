// Ex05bDoc.cpp : implementation of the CEx05bDoc class
//

#include "stdafx.h"
#include "Ex05b.h"

#include "Ex05bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx05bDoc

IMPLEMENT_DYNCREATE(CEx05bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx05bDoc, CDocument)
END_MESSAGE_MAP()


// CEx05bDoc construction/destruction

CEx05bDoc::CEx05bDoc()
{
	// TODO: add one-time construction code here

}

CEx05bDoc::~CEx05bDoc()
{
}

BOOL CEx05bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx05bDoc serialization

void CEx05bDoc::Serialize(CArchive& ar)
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


// CEx05bDoc diagnostics

#ifdef _DEBUG
void CEx05bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx05bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx05bDoc commands
