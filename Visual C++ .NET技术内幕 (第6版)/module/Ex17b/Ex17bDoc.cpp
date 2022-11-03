// Ex17bDoc.cpp : implementation of the CEx17bDoc class
//

#include "stdafx.h"
#include "Ex17b.h"

#include "Ex17bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx17bDoc

IMPLEMENT_DYNCREATE(CEx17bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx17bDoc, CDocument)
END_MESSAGE_MAP()


// CEx17bDoc construction/destruction

CEx17bDoc::CEx17bDoc()
{
	// TODO: add one-time construction code here

}

CEx17bDoc::~CEx17bDoc()
{
}

BOOL CEx17bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	int n1, n2, n3;
    // Make 50 random circles
    srand((unsigned) time(NULL));
    m_ellipseArray.SetSize(nMaxEllipses);

    for (int i = 0; i < nMaxEllipses; i++) {
        n1 = rand() * 600 / RAND_MAX;
        n2 = rand() * 600 / RAND_MAX;
        n3 = rand() * 50  / RAND_MAX;
        m_ellipseArray[i] = CRect(n1, -n2, n1 + n3, -(n2 + n3));
    }


	return TRUE;
}




// CEx17bDoc serialization

void CEx17bDoc::Serialize(CArchive& ar)
{
	m_ellipseArray.Serialize(ar);
}


// CEx17bDoc diagnostics

#ifdef _DEBUG
void CEx17bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx17bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEx17bDoc commands
