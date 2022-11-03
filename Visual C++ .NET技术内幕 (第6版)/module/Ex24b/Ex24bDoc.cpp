// Ex24bDoc.cpp : implementation of the CEx24bDoc class
//

#include "stdafx.h"
#include "Ex24b.h"

#include "Ex24bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx24bDoc

IMPLEMENT_DYNCREATE(CEx24bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx24bDoc, CDocument)
    ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
END_MESSAGE_MAP()


// CEx24bDoc construction/destruction

CEx24bDoc::CEx24bDoc()
{
	// TODO: add one-time construction code here

}

CEx24bDoc::~CEx24bDoc()
{
}

BOOL CEx24bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx24bDoc serialization

void CEx24bDoc::Serialize(CArchive& ar)
{
    m_dib.Serialize(ar);
}


// CEx24bDoc diagnostics

#ifdef _DEBUG
void CEx24bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx24bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx24bDoc commands

void CEx24bDoc::DeleteContents()
{
    m_dib.Empty();
}

void CEx24bDoc::OnEditClearall()
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
}
