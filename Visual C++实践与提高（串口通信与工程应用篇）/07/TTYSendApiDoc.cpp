// TTYSendApiDoc.cpp : implementation of the CTTYSendApiDoc class
//

#include "stdafx.h"
#include "TTYSendApi.h"

#include "TTYSendApiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiDoc

IMPLEMENT_DYNCREATE(CTTYSendApiDoc, CDocument)

BEGIN_MESSAGE_MAP(CTTYSendApiDoc, CDocument)
	//{{AFX_MSG_MAP(CTTYSendApiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiDoc construction/destruction

CTTYSendApiDoc::CTTYSendApiDoc()
{
	// TODO: add one-time construction code here

}

CTTYSendApiDoc::~CTTYSendApiDoc()
{
}

BOOL CTTYSendApiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiDoc serialization

void CTTYSendApiDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiDoc diagnostics

#ifdef _DEBUG
void CTTYSendApiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTTYSendApiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiDoc commands
