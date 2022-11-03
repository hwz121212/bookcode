// Ex11aDoc.cpp : implementation of the CEx11aDoc class
//

#include "stdafx.h"
#include "Ex11a.h"

#include "Ex11aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx11aDoc

IMPLEMENT_DYNCREATE(CEx11aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx11aDoc, CDocument)
END_MESSAGE_MAP()


// CEx11aDoc construction/destruction

CEx11aDoc::CEx11aDoc()
{
	// TODO: add one-time construction code here

}

CEx11aDoc::~CEx11aDoc()
{
}

BOOL CEx11aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx11aDoc serialization

void CEx11aDoc::Serialize(CArchive& ar)
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


// CEx11aDoc diagnostics

#ifdef _DEBUG
void CEx11aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx11aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx11aDoc commands
