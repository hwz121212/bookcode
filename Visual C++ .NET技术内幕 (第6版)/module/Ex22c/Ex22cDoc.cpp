// Ex22cDoc.cpp : implementation of the CEx22cDoc class
//

#include "stdafx.h"
#include "Ex22c.h"

#include "Ex22cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx22cDoc

IMPLEMENT_DYNCREATE(CEx22cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx22cDoc, CDocument)
END_MESSAGE_MAP()


// CEx22cDoc construction/destruction

CEx22cDoc::CEx22cDoc()
{
	// TODO: add one-time construction code here

}

CEx22cDoc::~CEx22cDoc()
{
}

BOOL CEx22cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx22cDoc serialization

void CEx22cDoc::Serialize(CArchive& ar)
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


// CEx22cDoc diagnostics

#ifdef _DEBUG
void CEx22cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx22cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx22cDoc commands
