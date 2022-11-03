// Ex05aDoc.cpp : implementation of the CEx05aDoc class
//

#include "stdafx.h"
#include "Ex05a.h"

#include "Ex05aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx05aDoc

IMPLEMENT_DYNCREATE(CEx05aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx05aDoc, CDocument)
END_MESSAGE_MAP()


// CEx05aDoc construction/destruction

CEx05aDoc::CEx05aDoc()
{
	// TODO: add one-time construction code here

}

CEx05aDoc::~CEx05aDoc()
{
}

BOOL CEx05aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx05aDoc serialization

void CEx05aDoc::Serialize(CArchive& ar)
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


// CEx05aDoc diagnostics

#ifdef _DEBUG
void CEx05aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx05aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx05aDoc commands
