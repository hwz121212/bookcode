// Ex09aDoc.cpp : implementation of the CEx09aDoc class
//

#include "stdafx.h"
#include "Ex09a.h"

#include "Ex09aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx09aDoc

IMPLEMENT_DYNCREATE(CEx09aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx09aDoc, CDocument)
END_MESSAGE_MAP()


// CEx09aDoc construction/destruction

CEx09aDoc::CEx09aDoc()
{
	// TODO: add one-time construction code here

}

CEx09aDoc::~CEx09aDoc()
{
}

BOOL CEx09aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx09aDoc serialization

void CEx09aDoc::Serialize(CArchive& ar)
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


// CEx09aDoc diagnostics

#ifdef _DEBUG
void CEx09aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx09aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx09aDoc commands
