// MySplitterDoc.cpp : implementation of the CMySplitterDoc class
//

#include "stdafx.h"
#include "MySplitter.h"

#include "MySplitterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySplitterDoc

IMPLEMENT_DYNCREATE(CMySplitterDoc, CDocument)

BEGIN_MESSAGE_MAP(CMySplitterDoc, CDocument)
	//{{AFX_MSG_MAP(CMySplitterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySplitterDoc construction/destruction

CMySplitterDoc::CMySplitterDoc()
{
	// TODO: add one-time construction code here

}

CMySplitterDoc::~CMySplitterDoc()
{
}

BOOL CMySplitterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMySplitterDoc serialization

void CMySplitterDoc::Serialize(CArchive& ar)
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
// CMySplitterDoc diagnostics

#ifdef _DEBUG
void CMySplitterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySplitterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySplitterDoc commands
