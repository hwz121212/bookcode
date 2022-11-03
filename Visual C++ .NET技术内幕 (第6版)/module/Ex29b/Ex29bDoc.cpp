// Ex29bDoc.cpp : implementation of the CEx29bDoc class
//

#include "stdafx.h"
#include "Ex29b.h"

#include "Ex29bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx29bDoc

IMPLEMENT_DYNCREATE(CEx29bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx29bDoc, CDocument)
END_MESSAGE_MAP()


// CEx29bDoc construction/destruction

CEx29bDoc::CEx29bDoc()
{
	// TODO: add one-time construction code here

}

CEx29bDoc::~CEx29bDoc()
{
}

BOOL CEx29bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx29bDoc serialization

void CEx29bDoc::Serialize(CArchive& ar)
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


// CEx29bDoc diagnostics

#ifdef _DEBUG
void CEx29bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx29bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx29bDoc commands
