// MyTimerDoc.cpp : implementation of the CMyTimerDoc class
//

#include "stdafx.h"
#include "MyTimer.h"

#include "MyTimerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTimerDoc

IMPLEMENT_DYNCREATE(CMyTimerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyTimerDoc, CDocument)
	//{{AFX_MSG_MAP(CMyTimerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTimerDoc construction/destruction

CMyTimerDoc::CMyTimerDoc()
{
	// TODO: add one-time construction code here

}

CMyTimerDoc::~CMyTimerDoc()
{
}

BOOL CMyTimerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyTimerDoc serialization

void CMyTimerDoc::Serialize(CArchive& ar)
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
// CMyTimerDoc diagnostics

#ifdef _DEBUG
void CMyTimerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyTimerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTimerDoc commands
