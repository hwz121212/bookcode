// BarProgressDoc.cpp : implementation of the CBarProgressDoc class
//

#include "stdafx.h"
#include "BarProgress.h"

#include "BarProgressDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarProgressDoc

IMPLEMENT_DYNCREATE(CBarProgressDoc, CDocument)

BEGIN_MESSAGE_MAP(CBarProgressDoc, CDocument)
	//{{AFX_MSG_MAP(CBarProgressDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarProgressDoc construction/destruction

CBarProgressDoc::CBarProgressDoc()
{
	// TODO: add one-time construction code here

}

CBarProgressDoc::~CBarProgressDoc()
{
}

BOOL CBarProgressDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBarProgressDoc serialization

void CBarProgressDoc::Serialize(CArchive& ar)
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
// CBarProgressDoc diagnostics

#ifdef _DEBUG
void CBarProgressDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBarProgressDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarProgressDoc commands
