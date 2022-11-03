// DynMenuDoc.cpp : implementation of the CDynMenuDoc class
//

#include "stdafx.h"
#include "DynMenu.h"

#include "DynMenuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc

IMPLEMENT_DYNCREATE(CDynMenuDoc, CDocument)

BEGIN_MESSAGE_MAP(CDynMenuDoc, CDocument)
	//{{AFX_MSG_MAP(CDynMenuDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc construction/destruction

CDynMenuDoc::CDynMenuDoc()
{
	// TODO: add one-time construction code here

}

CDynMenuDoc::~CDynMenuDoc()
{
}

BOOL CDynMenuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc serialization

void CDynMenuDoc::Serialize(CArchive& ar)
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
// CDynMenuDoc diagnostics

#ifdef _DEBUG
void CDynMenuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDynMenuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc commands
