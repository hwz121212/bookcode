// Ex06eDoc.cpp : implementation of the CEx06eDoc class
//

#include "stdafx.h"
#include "Ex06e.h"

#include "Ex06eDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx06eDoc

IMPLEMENT_DYNCREATE(CEx06eDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx06eDoc, CDocument)
END_MESSAGE_MAP()


// CEx06eDoc construction/destruction

CEx06eDoc::CEx06eDoc()
{
	// TODO: add one-time construction code here

}

CEx06eDoc::~CEx06eDoc()
{
}

BOOL CEx06eDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx06eDoc serialization

void CEx06eDoc::Serialize(CArchive& ar)
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


// CEx06eDoc diagnostics

#ifdef _DEBUG
void CEx06eDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx06eDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx06eDoc commands
