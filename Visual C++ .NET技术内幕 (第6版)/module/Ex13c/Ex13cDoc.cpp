// Ex13cDoc.cpp : implementation of the CEx13cDoc class
//

#include "stdafx.h"
#include "Ex13c.h"

#include "Ex13cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx13cDoc

IMPLEMENT_DYNCREATE(CEx13cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx13cDoc, CDocument)
END_MESSAGE_MAP()


// CEx13cDoc construction/destruction

CEx13cDoc::CEx13cDoc()
{
	// TODO: add one-time construction code here

}

CEx13cDoc::~CEx13cDoc()
{
}

BOOL CEx13cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx13cDoc serialization

void CEx13cDoc::Serialize(CArchive& ar)
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


// CEx13cDoc diagnostics

#ifdef _DEBUG
void CEx13cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx13cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx13cDoc commands
