// Print2Doc.cpp : implementation of the CPrint2Doc class
//

#include "stdafx.h"
#include "Print2.h"

#include "Print2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrint2Doc

IMPLEMENT_DYNCREATE(CPrint2Doc, CDocument)

BEGIN_MESSAGE_MAP(CPrint2Doc, CDocument)
	//{{AFX_MSG_MAP(CPrint2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrint2Doc construction/destruction

CPrint2Doc::CPrint2Doc()
{
	// TODO: add one-time construction code here

}

CPrint2Doc::~CPrint2Doc()
{
}

BOOL CPrint2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
     int i,j,k;
	 srand((unsigned int)time(NULL));
	 m_rectArray.SetSize(nMaxRect);
	 for(int n=0;n<nMaxRect;n++)
	 {
		 i=rand()*700/RAND_MAX;
		 j=rand()*700/RAND_MAX;
		 k=rand()*60/RAND_MAX;
		 m_rectArray[n]=CRect(i,-j,i+k,-j-k);
	 }
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPrint2Doc serialization

void CPrint2Doc::Serialize(CArchive& ar)
{
	m_rectArray.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPrint2Doc diagnostics

#ifdef _DEBUG
void CPrint2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrint2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrint2Doc commands
