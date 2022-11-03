// OpenDlgView.cpp : implementation of the COpenDlgView class
//

#include "stdafx.h"
#include "OpenDlg.h"

#include "OpenDlgDoc.h"
#include "OpenDlgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenDlgView

IMPLEMENT_DYNCREATE(COpenDlgView, CView)

BEGIN_MESSAGE_MAP(COpenDlgView, CView)
	//{{AFX_MSG_MAP(COpenDlgView)
	ON_COMMAND(ID_FILEOPEN, OnFileopen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenDlgView construction/destruction

COpenDlgView::COpenDlgView()
{
	// TODO: add construction code here

}

COpenDlgView::~COpenDlgView()
{
}

BOOL COpenDlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenDlgView drawing

void COpenDlgView::OnDraw(CDC* pDC)
{
	COpenDlgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(0,0,FileName);
	pDC->TextOut(0,40,FilePathname);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COpenDlgView printing

BOOL COpenDlgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenDlgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenDlgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COpenDlgView diagnostics

#ifdef _DEBUG
void COpenDlgView::AssertValid() const
{
	CView::AssertValid();
}

void COpenDlgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenDlgDoc* COpenDlgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenDlgDoc)));
	return (COpenDlgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenDlgView message handlers



void COpenDlgView::OnFileopen() 
{
CFileDialog dlg( TRUE,_T("TXT"),_T("*.TXT"),
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("文本文件 (*.TXT)|*.TXT|"));	


if(IDOK==dlg.DoModal())
{
    FilePathname.Format("%s %s","filepath:",dlg.GetPathName());
	FileName.Format("%s %s","filename:",dlg.GetFileName());
}
	Invalidate();
}
