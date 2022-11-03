// FormColorDoc.cpp : implementation of the CFormColorDoc class
//

#include "stdafx.h"
#include "FormColor.h"

#include "FormColorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormColorDoc

IMPLEMENT_DYNCREATE(CFormColorDoc, CDocument)

BEGIN_MESSAGE_MAP(CFormColorDoc, CDocument)
	//{{AFX_MSG_MAP(CFormColorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormColorDoc construction/destruction

CFormColorDoc::CFormColorDoc()
{
	// TODO: add one-time construction code here

}

CFormColorDoc::~CFormColorDoc()
{
}

BOOL CFormColorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFormColorDoc serialization

void CFormColorDoc::Serialize(CArchive& ar)
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
// CFormColorDoc diagnostics

#ifdef _DEBUG
void CFormColorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFormColorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormColorDoc commands
