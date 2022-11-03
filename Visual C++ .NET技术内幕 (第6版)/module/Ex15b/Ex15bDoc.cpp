// Ex15bDoc.cpp : implementation of the CEx15bDoc class
//

#include "stdafx.h"
#include "Ex15b.h"

#include "Ex15bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx15bDoc

IMPLEMENT_DYNCREATE(CEx15bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx15bDoc, CDocument)
	ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
END_MESSAGE_MAP()


// CEx15bDoc construction/destruction

CEx15bDoc::CEx15bDoc()
{
	TRACE("Entering CEx15bDoc constructor\n");
#ifdef _DEBUG
    afxDump.SetDepth(1); // Ensure dump of list elements
#endif // _DEBUG


}

CEx15bDoc::~CEx15bDoc()
{
}

BOOL CEx15bDoc::OnNewDocument()
{
	TRACE("Entering CEx15bDoc::OnNewDocument\n");
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx15bDoc serialization

void CEx15bDoc::Serialize(CArchive& ar)
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


// CEx15bDoc diagnostics

#ifdef _DEBUG
void CEx15bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx15bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
    dc << "\n" << m_studentList << "\n";

}
#endif //_DEBUG


// CEx15bDoc commands

void CEx15bDoc::DeleteContents()
{
#ifdef _DEBUG
    Dump(afxDump);
#endif
    while (m_studentList.GetHeadPosition()) {
        delete m_studentList.RemoveHead();
    }

}


void CEx15bDoc::OnEditClearall()
{
	DeleteContents();
    UpdateAllViews(NULL);

}

void CEx15bDoc::OnUpdateEditClearall(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_studentList.IsEmpty());
}
