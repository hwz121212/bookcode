// MyMsgDoc.cpp : implementation of the CMyMsgDoc class
//

#include "stdafx.h"
#include "MyMsg.h"

#include "MyMsgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMsgDoc

IMPLEMENT_DYNCREATE(CMyMsgDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyMsgDoc, CDocument)
	//{{AFX_MSG_MAP(CMyMsgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMsgDoc construction/destruction

CMyMsgDoc::CMyMsgDoc()
{
	// TODO: add one-time construction code here

}

CMyMsgDoc::~CMyMsgDoc()
{
}

BOOL CMyMsgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyMsgDoc serialization

void CMyMsgDoc::Serialize(CArchive& ar)
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
// CMyMsgDoc diagnostics

#ifdef _DEBUG
void CMyMsgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyMsgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyMsgDoc commands
