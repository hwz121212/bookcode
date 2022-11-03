// Ex06dDoc.cpp : implementation of the CEx06dDoc class
//

#include "stdafx.h"
#include "Ex06d.h"

#include "Ex06dDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06dDoc

IMPLEMENT_DYNCREATE(CEx06dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx06dDoc, CDocument)
END_MESSAGE_MAP()


// CEx06dDoc construction/destruction

CEx06dDoc::CEx06dDoc()
{
	// TODO: add one-time construction code here

}

CEx06dDoc::~CEx06dDoc()
{
}

BOOL CEx06dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx06dDoc serialization

void CEx06dDoc::Serialize(CArchive& ar)
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


// CEx06dDoc diagnostics

#ifdef _DEBUG
void CEx06dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx06dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx06dDoc commands
