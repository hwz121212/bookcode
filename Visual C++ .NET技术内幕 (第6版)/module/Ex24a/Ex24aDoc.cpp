// Ex24aDoc.cpp : implementation of the CEx24aDoc class
//

#include "stdafx.h"
#include "Ex24a.h"

#include "Ex24aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx24aDoc

IMPLEMENT_DYNCREATE(CEx24aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx24aDoc, CDocument)
    ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
END_MESSAGE_MAP()


// CEx24aDoc construction/destruction

CEx24aDoc::CEx24aDoc()
{
	// TODO: add one-time construction code here

}

CEx24aDoc::~CEx24aDoc()
{
}

BOOL CEx24aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx24aDoc serialization

void CEx24aDoc::Serialize(CArchive& ar)
{
   m_dib.Serialize(ar);
}


// CEx24aDoc diagnostics

#ifdef _DEBUG
void CEx24aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx24aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx24aDoc commands

void CEx24aDoc::OnEditClearall()
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
}

void CEx24aDoc::OnUpdateEditClearall(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_dib.GetSizeImage() > 0);   
}

void CEx24aDoc::DeleteContents()
{
   m_dib.Empty();
}
