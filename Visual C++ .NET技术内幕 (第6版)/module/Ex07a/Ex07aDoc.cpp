// Ex07aDoc.cpp : implementation of the CEx07aDoc class
//

#include "stdafx.h"
#include "Ex07a.h"

#include "Ex07aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx07aDoc

IMPLEMENT_DYNCREATE(CEx07aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx07aDoc, CDocument)
END_MESSAGE_MAP()


// CEx07aDoc construction/destruction

CEx07aDoc::CEx07aDoc()
{
	// TODO: add one-time construction code here

}

CEx07aDoc::~CEx07aDoc()
{
}

BOOL CEx07aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx07aDoc serialization

void CEx07aDoc::Serialize(CArchive& ar)
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


// CEx07aDoc diagnostics

#ifdef _DEBUG
void CEx07aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx07aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx07aDoc commands
