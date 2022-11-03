// Ex13aDoc.cpp : implementation of the CEx13aDoc class
//

#include "stdafx.h"
#include "Ex13a.h"

#include "Ex13aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx13aDoc

IMPLEMENT_DYNCREATE(CEx13aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx13aDoc, CDocument)
END_MESSAGE_MAP()


// CEx13aDoc construction/destruction

CEx13aDoc::CEx13aDoc()
{
	// TODO: add one-time construction code here

}

CEx13aDoc::~CEx13aDoc()
{
}

BOOL CEx13aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx13aDoc serialization

void CEx13aDoc::Serialize(CArchive& ar)
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


// CEx13aDoc diagnostics

#ifdef _DEBUG
void CEx13aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx13aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx13aDoc commands
