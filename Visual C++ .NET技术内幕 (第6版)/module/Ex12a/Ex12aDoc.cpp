// Ex12aDoc.cpp : implementation of the CEx12aDoc class
//

#include "stdafx.h"
#include "Ex12a.h"

#include "Ex12aDoc.h"
#include "Ex12aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx12aDoc

IMPLEMENT_DYNCREATE(CEx12aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx12aDoc, CDocument)
	ON_COMMAND(ID_EDIT_CLEARDOCUMENT, OnEditCleardocument)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARDOCUMENT, OnUpdateEditCleardocument)
END_MESSAGE_MAP()


// CEx12aDoc construction/destruction

CEx12aDoc::CEx12aDoc()
{
	// TODO: add one-time construction code here

}

CEx12aDoc::~CEx12aDoc()
{
}

BOOL CEx12aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	    m_strText = "Hello (from CEx12aDoc::OnNewDocument)";

	return TRUE;
}




// CEx12aDoc serialization

void CEx12aDoc::Serialize(CArchive& ar)
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


// CEx12aDoc diagnostics

#ifdef _DEBUG
void CEx12aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx12aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx12aDoc commands

void CEx12aDoc::OnEditCleardocument()
{
	m_strText.Empty();
	
	//reflect changes to the views
	POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
      CEx12aView* pView = (CEx12aView*) GetNextView(pos);
      pView->m_rich.SetWindowText(m_strText);
   }  
}

void CEx12aDoc::OnUpdateEditCleardocument(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_strText.IsEmpty());
}
