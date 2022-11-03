// MyCursorDoc.cpp : implementation of the CMyCursorDoc class
//

#include "stdafx.h"
#include "MyCursor.h"

#include "MyCursorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCursorDoc

IMPLEMENT_DYNCREATE(CMyCursorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyCursorDoc, CDocument)
	//{{AFX_MSG_MAP(CMyCursorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCursorDoc construction/destruction

CMyCursorDoc::CMyCursorDoc()
{
	// TODO: add one-time construction code here

}

CMyCursorDoc::~CMyCursorDoc()
{
}

BOOL CMyCursorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyCursorDoc serialization

void CMyCursorDoc::Serialize(CArchive& ar)
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
// CMyCursorDoc diagnostics

#ifdef _DEBUG
void CMyCursorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCursorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCursorDoc commands
