// ex16aDoc.cpp : implementation of the CEx16aDoc class
//

#include "stdafx.h"
#include "ex16a.h"

#include "ex16aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx16aDoc

IMPLEMENT_DYNCREATE(CEx16aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx16aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx16aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx16aDoc construction/destruction

CEx16aDoc::CEx16aDoc() : m_student("default value", 0)
{
    TRACE("Document object constructed\n");
}

CEx16aDoc::~CEx16aDoc()
{
#ifdef _DEBUG
    Dump(afxDump);
#endif // _DEBUG
}

BOOL CEx16aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx16aDoc serialization

void CEx16aDoc::Serialize(CArchive& ar)
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
// CEx16aDoc diagnostics

#ifdef _DEBUG
void CEx16aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx16aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
    dc << "\n" << m_student << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx16aDoc commands
