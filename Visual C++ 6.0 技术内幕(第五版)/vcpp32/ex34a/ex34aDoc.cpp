// ex34aDoc.cpp : implementation of the CEx34aDoc class
//

#include "stdafx.h"
#include "ex34a.h"

#include "ex34aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx34aDoc

IMPLEMENT_DYNCREATE(CEx34aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx34aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx34aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx34aDoc construction/destruction

CEx34aDoc::CEx34aDoc()
{
	// TODO: add one-time construction code here

}

CEx34aDoc::~CEx34aDoc()
{
}

BOOL CEx34aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx34aDoc serialization

void CEx34aDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx34aDoc diagnostics

#ifdef _DEBUG
void CEx34aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx34aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx34aDoc commands

BOOL CEx34aDoc::SaveModified() 
{
	return TRUE; // eliminates "save doc" message on exit
}
