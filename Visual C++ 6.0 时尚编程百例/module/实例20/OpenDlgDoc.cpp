// OpenDlgDoc.cpp : implementation of the COpenDlgDoc class
//

#include "stdafx.h"
#include "OpenDlg.h"

#include "OpenDlgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenDlgDoc

IMPLEMENT_DYNCREATE(COpenDlgDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenDlgDoc, CDocument)
	//{{AFX_MSG_MAP(COpenDlgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenDlgDoc construction/destruction

COpenDlgDoc::COpenDlgDoc()
{
	// TODO: add one-time construction code here

}

COpenDlgDoc::~COpenDlgDoc()
{
}

BOOL COpenDlgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COpenDlgDoc serialization

void COpenDlgDoc::Serialize(CArchive& ar)
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
// COpenDlgDoc diagnostics

#ifdef _DEBUG
void COpenDlgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenDlgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenDlgDoc commands
