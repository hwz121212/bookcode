// CharviewDoc.cpp : implementation of the CCharviewDoc class
//

#include "stdafx.h"
#include "Charview.h"

#include "CharviewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharviewDoc

IMPLEMENT_DYNCREATE(CCharviewDoc, CDocument)

BEGIN_MESSAGE_MAP(CCharviewDoc, CDocument)
	//{{AFX_MSG_MAP(CCharviewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharviewDoc construction/destruction

CCharviewDoc::CCharviewDoc()
{
	
    number=0;

}

CCharviewDoc::~CCharviewDoc()
{
}

BOOL CCharviewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCharviewDoc serialization

void CCharviewDoc::Serialize(CArchive& ar)
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
// CCharviewDoc diagnostics

#ifdef _DEBUG
void CCharviewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCharviewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCharviewDoc commands
