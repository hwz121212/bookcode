// DlgBarDoc.cpp : implementation of the CDlgBarDoc class
//

#include "stdafx.h"
#include "DlgBar.h"

#include "DlgBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBarDoc

IMPLEMENT_DYNCREATE(CDlgBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CDlgBarDoc, CDocument)
	//{{AFX_MSG_MAP(CDlgBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBarDoc construction/destruction

CDlgBarDoc::CDlgBarDoc()
{
	// TODO: add one-time construction code here

}

CDlgBarDoc::~CDlgBarDoc()
{
}

BOOL CDlgBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDlgBarDoc serialization

void CDlgBarDoc::Serialize(CArchive& ar)
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
// CDlgBarDoc diagnostics

#ifdef _DEBUG
void CDlgBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDlgBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgBarDoc commands
