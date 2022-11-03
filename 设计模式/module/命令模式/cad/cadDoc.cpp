// cadDoc.cpp : implementation of the CCadDoc class
//

#include "stdafx.h"
#include "cad.h"
#include "MainFrm.h"
#include "cadDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadDoc

IMPLEMENT_DYNCREATE(CCadDoc, CDocument)

BEGIN_MESSAGE_MAP(CCadDoc, CDocument)
	//{{AFX_MSG_MAP(CCadDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadDoc construction/destruction

CCadDoc::CCadDoc()
{
	// TODO: add one-time construction code here

}

CCadDoc::~CCadDoc()
{
}

BOOL CCadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCadDoc serialization

void CCadDoc::Serialize(CArchive& ar)
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
// CCadDoc diagnostics

#ifdef _DEBUG
void CCadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCadDoc commands

void CCadDoc::AddShape(CShape* pShape)
{
	m_ShapeCollection.Add(pShape);
}

void CCadDoc::RemoveShape(CShape* pShape)
{
	m_ShapeCollection.Remove(pShape);
}



