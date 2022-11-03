// Ex08aDoc.cpp : implementation of the CEx08aDoc class
//

#include "stdafx.h"
#include "Ex08a.h"

#include "Ex08aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx08aDoc

IMPLEMENT_DYNCREATE(CEx08aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx08aDoc, CDocument)
END_MESSAGE_MAP()


// CEx08aDoc construction/destruction

CEx08aDoc::CEx08aDoc()
{
	// TODO: add one-time construction code here

}

CEx08aDoc::~CEx08aDoc()
{
}

BOOL CEx08aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx08aDoc serialization

void CEx08aDoc::Serialize(CArchive& ar)
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


// CEx08aDoc diagnostics

#ifdef _DEBUG
void CEx08aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx08aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx08aDoc commands
