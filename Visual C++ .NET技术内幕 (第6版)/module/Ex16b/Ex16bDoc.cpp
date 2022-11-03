// Ex16bDoc.cpp : implementation of the CEx16bDoc class
//

#include "stdafx.h"
#include "Ex16b.h"

#include "Ex16bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx16bDoc

IMPLEMENT_DYNCREATE(CEx16bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx16bDoc, CDocument)
	ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
END_MESSAGE_MAP()


// CEx16bDoc construction/destruction

CEx16bDoc::CEx16bDoc()
{
	TRACE("Entering CEx16bDoc constructor\n");
#ifdef _DEBUG
    afxDump.SetDepth(1); // Ensure dump of list elements
#endif // _DEBUG

}

CEx16bDoc::~CEx16bDoc()
{
}

BOOL CEx16bDoc::OnNewDocument()
{
	TRACE("Entering CEx16bDoc::OnNewDocument\n");
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx16bDoc serialization

void CEx16bDoc::Serialize(CArchive& ar)
{
	TRACE("Entering CEx16bDoc::Serialize\n");
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	m_studentList.Serialize(ar);
}


// CEx16bDoc diagnostics

#ifdef _DEBUG
void CEx16bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx16bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx16bDoc commands
void CEx16bDoc::DeleteContents()
{
    TRACE("Entering CEx16b::DeleteContents\n");
#ifdef _DEBUG
    Dump(afxDump);
#endif
    while (m_studentList.GetHeadPosition()) {
        delete m_studentList.RemoveHead();
    }
}

void CEx16bDoc::OnEditClearall()
{
    DeleteContents();
    UpdateAllViews(NULL);
}

void CEx16bDoc::OnUpdateEditClearall(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!m_studentList.IsEmpty());
}

BOOL CEx16bDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    TRACE("Entering CEx16b::OnOpenDocument\n");
     if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;
	
    // TODO: Add your specialized creation code here
	
    return TRUE;
}

void CEx16bDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
    // Disable disk toolbar button if file is not modified
    pCmdUI->Enable(IsModified());
}

