// AcceleratorDoc.cpp : implementation of the CAcceleratorDoc class
//

#include "stdafx.h"
#include "Accelerator.h"

#include "AcceleratorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorDoc

IMPLEMENT_DYNCREATE(CAcceleratorDoc, CDocument)

BEGIN_MESSAGE_MAP(CAcceleratorDoc, CDocument)
	//{{AFX_MSG_MAP(CAcceleratorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorDoc construction/destruction

CAcceleratorDoc::CAcceleratorDoc()
{
	// TODO: add one-time construction code here

}

CAcceleratorDoc::~CAcceleratorDoc()
{
}

BOOL CAcceleratorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAcceleratorDoc serialization

void CAcceleratorDoc::Serialize(CArchive& ar)
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
// CAcceleratorDoc diagnostics

#ifdef _DEBUG
void CAcceleratorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAcceleratorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAcceleratorDoc commands
