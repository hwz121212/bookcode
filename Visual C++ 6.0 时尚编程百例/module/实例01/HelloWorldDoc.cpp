// HelloWorldDoc.cpp : implementation of the CHelloWorldDoc class
//

#include "stdafx.h"
#include "HelloWorld.h"

#include "HelloWorldDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelloWorldDoc

IMPLEMENT_DYNCREATE(CHelloWorldDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelloWorldDoc, CDocument)
	//{{AFX_MSG_MAP(CHelloWorldDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelloWorldDoc construction/destruction

CHelloWorldDoc::CHelloWorldDoc()
{
	// TODO: add one-time construction code here

}

CHelloWorldDoc::~CHelloWorldDoc()
{
}

BOOL CHelloWorldDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHelloWorldDoc serialization

void CHelloWorldDoc::Serialize(CArchive& ar)
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
// CHelloWorldDoc diagnostics

#ifdef _DEBUG
void CHelloWorldDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelloWorldDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelloWorldDoc commands
