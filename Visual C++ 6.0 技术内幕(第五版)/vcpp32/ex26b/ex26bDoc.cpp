// ex26bDoc.cpp : implementation of the CEx26bDoc class
//

#include "stdafx.h"
#include "ex26b.h"

#include "CDib.h"
#include "ex26bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc

IMPLEMENT_DYNCREATE(CEx26bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx26bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx26bDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc construction/destruction

CEx26bDoc::CEx26bDoc()
{
    m_bDragHere = FALSE;

}

CEx26bDoc::~CEx26bDoc()
{
}

BOOL CEx26bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc serialization

void CEx26bDoc::Serialize(CArchive& ar)
{
    m_dib.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc diagnostics

#ifdef _DEBUG
void CEx26bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx26bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc commands

void CEx26bDoc::DeleteContents() 
{
    m_dib.Empty();
}

void CEx26bDoc::OnEditClearAll() 
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
	
}

void CEx26bDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_dib.GetSizeImage() > 0);   
	
}
