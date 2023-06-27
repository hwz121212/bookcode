// ex13aDoc.cpp : implementation of the CEx13aDoc class
//

#include "stdafx.h"
#include "ex13a.h"

#include "ex13aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx13aDoc

IMPLEMENT_DYNCREATE(CEx13aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx13aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx13aDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearDocument)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx13aDoc construction/destruction

CEx13aDoc::CEx13aDoc()
{
	// TODO: add one-time construction code here

}

CEx13aDoc::~CEx13aDoc()
{
}

BOOL CEx13aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_strText = "Hello (from CEx13aDoc::OnNewDocument)";
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx13aDoc serialization

void CEx13aDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CEx13aDoc diagnostics

#ifdef _DEBUG
void CEx13aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx13aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx13aDoc commands

void CEx13aDoc::OnEditClearDocument() 
{
	m_strText.Empty();	
}

void CEx13aDoc::OnUpdateEditClearDocument(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_strText.IsEmpty());	
}
