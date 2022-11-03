// Ex07cDoc.cpp : implementation of the CEx07cDoc class
//

#include "stdafx.h"
#include "Ex07c.h"

#include "Ex07cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx07cDoc

IMPLEMENT_DYNCREATE(CEx07cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx07cDoc, CDocument)
END_MESSAGE_MAP()


// CEx07cDoc construction/destruction

CEx07cDoc::CEx07cDoc()
{
	// TODO: add one-time construction code here

}

CEx07cDoc::~CEx07cDoc()
{
}

BOOL CEx07cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx07cDoc serialization

void CEx07cDoc::Serialize(CArchive& ar)
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


// CEx07cDoc diagnostics

#ifdef _DEBUG
void CEx07cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx07cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx07cDoc commands
