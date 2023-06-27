// PC2PLCDoc.cpp : implementation of the CPC2PLCDoc class
//

#include "stdafx.h"
#include "PC2PLC.h"

#include "PC2PLCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCDoc

IMPLEMENT_DYNCREATE(CPC2PLCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPC2PLCDoc, CDocument)
	//{{AFX_MSG_MAP(CPC2PLCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCDoc construction/destruction

CPC2PLCDoc::CPC2PLCDoc()
{
	// TODO: add one-time construction code here

}

CPC2PLCDoc::~CPC2PLCDoc()
{
}

BOOL CPC2PLCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPC2PLCDoc serialization

void CPC2PLCDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCDoc diagnostics

#ifdef _DEBUG
void CPC2PLCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPC2PLCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPC2PLCDoc commands
