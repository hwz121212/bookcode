// ListboxDoc.cpp : implementation of the CListboxDoc class
//

#include "stdafx.h"
#include "Listbox.h"

#include "ListboxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListboxDoc

IMPLEMENT_DYNCREATE(CListboxDoc, CDocument)

BEGIN_MESSAGE_MAP(CListboxDoc, CDocument)
	//{{AFX_MSG_MAP(CListboxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListboxDoc construction/destruction

CListboxDoc::CListboxDoc()
{
	// TODO: add one-time construction code here

}

CListboxDoc::~CListboxDoc()
{
}

BOOL CListboxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CListboxDoc serialization

void CListboxDoc::Serialize(CArchive& ar)
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
// CListboxDoc diagnostics

#ifdef _DEBUG
void CListboxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CListboxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListboxDoc commands
