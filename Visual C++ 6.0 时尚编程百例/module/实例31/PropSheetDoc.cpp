// PropSheetDoc.cpp : implementation of the CPropSheetDoc class
//

#include "stdafx.h"
#include "PropSheet.h"

#include "PropSheetDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropSheetDoc

IMPLEMENT_DYNCREATE(CPropSheetDoc, CDocument)

BEGIN_MESSAGE_MAP(CPropSheetDoc, CDocument)
	//{{AFX_MSG_MAP(CPropSheetDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropSheetDoc construction/destruction

CPropSheetDoc::CPropSheetDoc()
{
	// TODO: add one-time construction code here

}

CPropSheetDoc::~CPropSheetDoc()
{
}

BOOL CPropSheetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPropSheetDoc serialization

void CPropSheetDoc::Serialize(CArchive& ar)
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
// CPropSheetDoc diagnostics

#ifdef _DEBUG
void CPropSheetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPropSheetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropSheetDoc commands
