// ex26aDoc.cpp : implementation of the CEx26aDoc class
//

#include "stdafx.h"
#include "ex26a.h"

#include "cdib.h"
#include "ex26aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc

IMPLEMENT_DYNCREATE(CEx26aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx26aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx26aDoc)
   ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc construction/destruction

CEx26aDoc::CEx26aDoc()
{
	// TODO: add one-time construction code here

}

CEx26aDoc::~CEx26aDoc()
{
}

BOOL CEx26aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc serialization

void CEx26aDoc::Serialize(CArchive& ar)
{
   m_dib.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc diagnostics

#ifdef _DEBUG
void CEx26aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx26aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26aDoc commands

void CEx26aDoc::OnEditClearAll() 
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
}

void CEx26aDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_dib.GetSizeImage() > 0);   
}

void CEx26aDoc::DeleteContents() 
{
   m_dib.Empty();
}
