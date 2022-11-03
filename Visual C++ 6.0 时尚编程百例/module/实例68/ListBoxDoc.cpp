// ListBoxDoc.cpp : implementation of the CListBoxDoc class
//

#include "stdafx.h"
#include "ListBox.h"

#include "ListBoxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxDoc

IMPLEMENT_DYNCREATE(CListBoxDoc, CDocument)

BEGIN_MESSAGE_MAP(CListBoxDoc, CDocument)
	//{{AFX_MSG_MAP(CListBoxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxDoc construction/destruction

CListBoxDoc::CListBoxDoc()
{
	// TODO: add one-time construction code here

}

CListBoxDoc::~CListBoxDoc()
{
}

BOOL CListBoxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CListBoxDoc serialization

void CListBoxDoc::Serialize(CArchive& ar)
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
// CListBoxDoc diagnostics

#ifdef _DEBUG
void CListBoxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CListBoxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListBoxDoc commands
