// Ex11cDoc.cpp : implementation of the CEx11cDoc class
//

#include "stdafx.h"
#include "Ex11c.h"

#include "Ex11cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx11cDoc

IMPLEMENT_DYNCREATE(CEx11cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx11cDoc, CDocument)
END_MESSAGE_MAP()


// CEx11cDoc construction/destruction

CEx11cDoc::CEx11cDoc()
{
	// TODO: add one-time construction code here

}

CEx11cDoc::~CEx11cDoc()
{
}

BOOL CEx11cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx11cDoc serialization

void CEx11cDoc::Serialize(CArchive& ar)
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


// CEx11cDoc diagnostics

#ifdef _DEBUG
void CEx11cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx11cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx11cDoc commands
