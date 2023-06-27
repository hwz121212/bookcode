// PC2PCDoc.cpp : implementation of the CPC2PCDoc class
//

#include "stdafx.h"
#include "PC2PC.h"

#include "PC2PCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPC2PCDoc

IMPLEMENT_DYNCREATE(CPC2PCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPC2PCDoc, CDocument)
	//{{AFX_MSG_MAP(CPC2PCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPC2PCDoc construction/destruction

CPC2PCDoc::CPC2PCDoc()
{
	// TODO: add one-time construction code here

}

CPC2PCDoc::~CPC2PCDoc()
{
}

BOOL CPC2PCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPC2PCDoc serialization

void CPC2PCDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPC2PCDoc diagnostics

#ifdef _DEBUG
void CPC2PCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPC2PCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPC2PCDoc commands
