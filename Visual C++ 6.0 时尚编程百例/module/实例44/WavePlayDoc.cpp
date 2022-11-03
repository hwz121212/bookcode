// WavePlayDoc.cpp : implementation of the CWavePlayDoc class
//

#include "stdafx.h"
#include "WavePlay.h"

#include "WavePlayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWavePlayDoc

IMPLEMENT_DYNCREATE(CWavePlayDoc, CDocument)

BEGIN_MESSAGE_MAP(CWavePlayDoc, CDocument)
	//{{AFX_MSG_MAP(CWavePlayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavePlayDoc construction/destruction

CWavePlayDoc::CWavePlayDoc()
{
	// TODO: add one-time construction code here

}

CWavePlayDoc::~CWavePlayDoc()
{
}

BOOL CWavePlayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWavePlayDoc serialization

void CWavePlayDoc::Serialize(CArchive& ar)
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
// CWavePlayDoc diagnostics

#ifdef _DEBUG
void CWavePlayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWavePlayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWavePlayDoc commands
