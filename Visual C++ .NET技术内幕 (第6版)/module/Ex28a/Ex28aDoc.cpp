// Ex28aDoc.cpp : implementation of the CEx28aDoc class
//

#include "stdafx.h"
#include "Ex28a.h"

#include "Ex28aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx28aDoc

IMPLEMENT_DYNCREATE(CEx28aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx28aDoc, CDocument)
END_MESSAGE_MAP()


// CEx28aDoc construction/destruction

CEx28aDoc::CEx28aDoc()
{
	// TODO: add one-time construction code here

}

CEx28aDoc::~CEx28aDoc()
{
}

BOOL CEx28aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx28aDoc serialization

void CEx28aDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CEx28aDoc diagnostics

#ifdef _DEBUG
void CEx28aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx28aDoc commands
