// Ex16cDoc.cpp : implementation of the CEx16cDoc class
//

#include "stdafx.h"
#include "Ex16c.h"

#include "Ex16cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx16cDoc

IMPLEMENT_DYNCREATE(CEx16cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx16cDoc, CDocument)
	ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
END_MESSAGE_MAP()


// CEx16cDoc construction/destruction

CEx16cDoc::CEx16cDoc()
{
	TRACE("Entering CEx16cDoc constructor\n");
#ifdef _DEBUG
    afxDump.SetDepth(1); // Ensure dump of list elements
#endif // _DEBUG
}

CEx16cDoc::~CEx16cDoc()
{
}

BOOL CEx16cDoc::OnNewDocument()
{
	TRACE("Entering CEx16cDoc::OnNewDocument\n");
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx16cDoc serialization

void CEx16cDoc::Serialize(CArchive& ar)
{
	TRACE("Entering CEx16cDoc::Serialize\n");
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


// CEx16cDoc diagnostics

#ifdef _DEBUG
void CEx16cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx16cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx16cDoc commands
void CEx16cDoc::DeleteContents()
{
    TRACE("Entering CEx16c::DeleteContents\n");
#ifdef _DEBUG
    Dump(afxDump);
#endif
    while (m_studentList.GetHeadPosition()) {
        delete m_studentList.RemoveHead();
    }
}

void CEx16cDoc::OnEditClearall()
{
    DeleteContents();
    UpdateAllViews(NULL);
}

void CEx16cDoc::OnUpdateEditClearall(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!m_studentList.IsEmpty());
}

BOOL CEx16cDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    TRACE("Entering CEx16c::OnOpenDocument\n");
     if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;
	
    // TODO: Add your specialized creation code here
	
    return TRUE;
}

void CEx16cDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
    // Disable disk toolbar button if file is not modified
    pCmdUI->Enable(IsModified());
}


