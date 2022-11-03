// Ex23eDoc.cpp : implementation of the CEx23eDoc class
//

#include "stdafx.h"
#include "Ex23e.h"

#include "Ex23eDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx23eDoc

IMPLEMENT_DYNCREATE(CEx23eDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx23eDoc, CDocument)
END_MESSAGE_MAP()


// CEx23eDoc construction/destruction

CEx23eDoc::CEx23eDoc()
{
	// TODO: add one-time construction code here

}

CEx23eDoc::~CEx23eDoc()
{
}

BOOL CEx23eDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx23eDoc serialization

void CEx23eDoc::Serialize(CArchive& ar)
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


// CEx23eDoc diagnostics

#ifdef _DEBUG
void CEx23eDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx23eDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx23eDoc commands
