// switchDoc.cpp : implementation of the CSwitchDoc class
//

#include "stdafx.h"
#include "switch.h"

#include "switchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchDoc

IMPLEMENT_DYNCREATE(CSwitchDoc, CDocument)

BEGIN_MESSAGE_MAP(CSwitchDoc, CDocument)
	//{{AFX_MSG_MAP(CSwitchDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchDoc construction/destruction

CSwitchDoc::CSwitchDoc()
{
	// TODO: add one-time construction code here

}

CSwitchDoc::~CSwitchDoc()
{
}

BOOL CSwitchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSwitchDoc serialization

void CSwitchDoc::Serialize(CArchive& ar)
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
// CSwitchDoc diagnostics

#ifdef _DEBUG
void CSwitchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSwitchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitchDoc commands
