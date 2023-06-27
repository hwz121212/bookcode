// ex19bDoc.cpp : implementation of the CEx19bDoc class
//

#include "stdafx.h"
#include "ex19b.h"

#include "ex19bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx19bDoc

IMPLEMENT_DYNCREATE(CEx19bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx19bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx19bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx19bDoc construction/destruction

CEx19bDoc::CEx19bDoc()
{
	// TODO: add one-time construction code here

}

CEx19bDoc::~CEx19bDoc()
{
}

BOOL CEx19bDoc::OnNewDocument()
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



/////////////////////////////////////////////////////////////////////////////
// CEx19bDoc serialization

void CEx19bDoc::Serialize(CArchive& ar)
{
    m_ellipseArray.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx19bDoc diagnostics

#ifdef _DEBUG
void CEx19bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx19bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx19bDoc commands
