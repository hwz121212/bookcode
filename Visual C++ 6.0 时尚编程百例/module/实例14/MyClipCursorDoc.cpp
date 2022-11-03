// MyClipCursorDoc.cpp : implementation of the CMyClipCursorDoc class
//

#include "stdafx.h"
#include "MyClipCursor.h"

#include "MyClipCursorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorDoc

IMPLEMENT_DYNCREATE(CMyClipCursorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyClipCursorDoc, CDocument)
	//{{AFX_MSG_MAP(CMyClipCursorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorDoc construction/destruction

CMyClipCursorDoc::CMyClipCursorDoc()
{
	// TODO: add one-time construction code here

}

CMyClipCursorDoc::~CMyClipCursorDoc()
{
}

BOOL CMyClipCursorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorDoc serialization

void CMyClipCursorDoc::Serialize(CArchive& ar)
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
// CMyClipCursorDoc diagnostics

#ifdef _DEBUG
void CMyClipCursorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyClipCursorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyClipCursorDoc commands
