// TimerDoc.cpp : implementation of the CTimerDoc class
//

#include "stdafx.h"
#include "Timer.h"

#include "TimerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimerDoc

IMPLEMENT_DYNCREATE(CTimerDoc, CDocument)

BEGIN_MESSAGE_MAP(CTimerDoc, CDocument)
	//{{AFX_MSG_MAP(CTimerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDoc construction/destruction

CTimerDoc::CTimerDoc()
{
	// TODO: add one-time construction code here

}

CTimerDoc::~CTimerDoc()
{
}

BOOL CTimerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTimerDoc serialization

void CTimerDoc::Serialize(CArchive& ar)
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
// CTimerDoc diagnostics

#ifdef _DEBUG
void CTimerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTimerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTimerDoc commands
