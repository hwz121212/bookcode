// MyFileView.cpp : implementation of the CMyFileView class
//

#include "stdafx.h"
#include "MyFile.h"

#include "MyFileDoc.h"
#include "MyFileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileView

IMPLEMENT_DYNCREATE(CMyFileView, CView)

BEGIN_MESSAGE_MAP(CMyFileView, CView)
	//{{AFX_MSG_MAP(CMyFileView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFileView construction/destruction

CMyFileView::CMyFileView()
{
	// TODO: add construction code here

}

CMyFileView::~CMyFileView()
{
}

BOOL CMyFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyFileView drawing

void CMyFileView::OnDraw(CDC* pDC)
{
	
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyFileView printing

BOOL CMyFileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFileView diagnostics

#ifdef _DEBUG
void CMyFileView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFileDoc* CMyFileView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFileDoc)));
	return (CMyFileDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFileView message handlers


void CMyFileView::OnFileOpen() 
{
	CMyFileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString FilePathname;
	CString FileName;
	CDC*pDC=GetDC();
	CFile MyFile;
	CFileDialog dlg( TRUE,_T("TXT"),_T("*.TXT"),
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("文本文件 (*.TXT)|*.TXT|"));	
     

if(IDOK==dlg.DoModal())
{

	FilePathname.Format("%s %s","filepath:",dlg.GetPathName());
	FileName.Format("%s %s","Old file name:",dlg.GetFileName());
	MyFile.Open(dlg.GetFileName(),CFile::modeCreate|CFile::modeNoTruncate);
}
    pDC->TextOut(0,0,FileName);
	pDC->TextOut(0,20,FilePathname);
	pDC->TextOut(0,40,"文件以被打开");
//	Invalidate();
	
}
