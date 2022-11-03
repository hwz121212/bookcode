// Ex23dDoc.cpp : implementation of the CEx23dDoc class
//

#include "stdafx.h"
#include "Ex23d.h"

#include "Ex23dDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx23dDoc

IMPLEMENT_DYNCREATE(CEx23dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx23dDoc, CDocument)
END_MESSAGE_MAP()


// CEx23dDoc construction/destruction

CEx23dDoc::CEx23dDoc()
{
	// TODO: add one-time construction code here

}

CEx23dDoc::~CEx23dDoc()
{
}

BOOL CEx23dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx23dDoc serialization

void CEx23dDoc::Serialize(CArchive& ar)
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


// CEx23dDoc diagnostics

#ifdef _DEBUG
void CEx23dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx23dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx23dDoc commands
