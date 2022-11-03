// SystemTreeDoc.cpp : implementation of the CSystemTreeDoc class
//

#include "stdafx.h"
#include "SystemTree.h"

#include "SystemTreeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeDoc

IMPLEMENT_DYNCREATE(CSystemTreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CSystemTreeDoc, CDocument)
	//{{AFX_MSG_MAP(CSystemTreeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeDoc construction/destruction

CSystemTreeDoc::CSystemTreeDoc()
{
	// TODO: add one-time construction code here

}

CSystemTreeDoc::~CSystemTreeDoc()
{
}

BOOL CSystemTreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSystemTreeDoc serialization

void CSystemTreeDoc::Serialize(CArchive& ar)
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
// CSystemTreeDoc diagnostics

#ifdef _DEBUG
void CSystemTreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSystemTreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSystemTreeDoc commands
