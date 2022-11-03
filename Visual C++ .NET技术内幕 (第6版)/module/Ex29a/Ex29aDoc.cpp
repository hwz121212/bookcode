// Ex29aDoc.cpp : implementation of the CEx29aDoc class
//

#include "stdafx.h"
#include "Ex29a.h"

#include "Ex29aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx29aDoc

IMPLEMENT_DYNCREATE(CEx29aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx29aDoc, CDocument)
END_MESSAGE_MAP()


// CEx29aDoc construction/destruction

CEx29aDoc::CEx29aDoc()
{
	// TODO: add one-time construction code here

}

CEx29aDoc::~CEx29aDoc()
{
}

BOOL CEx29aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx29aDoc serialization

void CEx29aDoc::Serialize(CArchive& ar)
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


// CEx29aDoc diagnostics

#ifdef _DEBUG
void CEx29aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx29aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx29aDoc commands
