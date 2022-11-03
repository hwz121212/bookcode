// Ex16aDoc.cpp : implementation of the CEx16aDoc class
//

#include "stdafx.h"
#include "Ex16a.h"

#include "Ex16aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx16aDoc

IMPLEMENT_DYNCREATE(CEx16aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx16aDoc, CDocument)
	ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
END_MESSAGE_MAP()


// CEx16aDoc construction/destruction

CEx16aDoc::CEx16aDoc()
{
	TRACE("Entering CEx16aDoc constructor\n");
#ifdef _DEBUG
    afxDump.SetDepth(1); // Ensure dump of list elements
#endif // _DEBUG

}

CEx16aDoc::~CEx16aDoc()
{
}

BOOL CEx16aDoc::OnNewDocument()
{
	TRACE("Entering CEx16aDoc::OnNewDocument\n");
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx16aDoc serialization

void CEx16aDoc::Serialize(CArchive& ar)
{
	TRACE("Entering CEx16aDoc::Serialize\n");
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


// CEx16aDoc diagnostics

#ifdef _DEBUG
void CEx16aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx16aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx16aDoc commands

void CEx16aDoc::DeleteContents()
{
    TRACE("Entering CEx16a::DeleteContents\n");
#ifdef _DEBUG
    Dump(afxDump);
#endif
    while (m_studentList.GetHeadPosition()) {
        delete m_studentList.RemoveHead();
    }
}

void CEx16aDoc::OnEditClearall()
{
    DeleteContents();
    UpdateAllViews(NULL);
}

void CEx16aDoc::OnUpdateEditClearall(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!m_studentList.IsEmpty());
}

BOOL CEx16aDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    TRACE("Entering CEx16a::OnOpenDocument\n");
     if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;
	
    // TODO: Add your specialized creation code here
	
    return TRUE;
}

void CEx16aDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
    // Disable disk toolbar button if file is not modified
    pCmdUI->Enable(IsModified());
}

