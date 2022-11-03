// Ex15aDoc.cpp : implementation of the CEx15aDoc class
//

#include "stdafx.h"
#include "Ex15a.h"
#include "student.h"
#include "Ex15aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx15aDoc

IMPLEMENT_DYNCREATE(CEx15aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx15aDoc, CDocument)
END_MESSAGE_MAP()


// CEx15aDoc construction/destruction

CEx15aDoc::CEx15aDoc(): m_student("default value", 0)
{
    
	TRACE("Document object constructed\n");

}

CEx15aDoc::~CEx15aDoc()
{

#ifdef _DEBUG
    Dump(afxDump);
#endif // _DEBUG

}

BOOL CEx15aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEx15aDoc serialization

void CEx15aDoc::Serialize(CArchive& ar)
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


// CEx15aDoc diagnostics

#ifdef _DEBUG
void CEx15aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx15aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
	dc << "\n" << m_student << "\n";
}
#endif //_DEBUG


// CEx15aDoc commands
