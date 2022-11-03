// ShowBmpView.cpp : implementation of the CShowBmpView class
//

#include "stdafx.h"
#include "ShowBmp.h"

#include "ShowBmpDoc.h"
#include "ShowBmpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowBmpView

IMPLEMENT_DYNCREATE(CShowBmpView, CView)

BEGIN_MESSAGE_MAP(CShowBmpView, CView)
	//{{AFX_MSG_MAP(CShowBmpView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowBmpView construction/destruction

CShowBmpView::CShowBmpView()
{
	// TODO: add construction code here
    State=0;
}

CShowBmpView::~CShowBmpView()
{
}

BOOL CShowBmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShowBmpView drawing

void CShowBmpView::OnDraw(CDC* pDC)
{
	CShowBmpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(State==1)
	{
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(pDC))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	// show the image.
    dcImage.SelectObject(&m_bitmap);
	pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
    
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CShowBmpView printing

BOOL CShowBmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CShowBmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CShowBmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CShowBmpView diagnostics

#ifdef _DEBUG
void CShowBmpView::AssertValid() const
{
	CView::AssertValid();
}

void CShowBmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShowBmpDoc* CShowBmpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShowBmpDoc)));
	return (CShowBmpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowBmpView message handlers

void CShowBmpView::OnFileOpen() 
{
CFileDialog dlg( TRUE,_T("BMP"),_T("*.BMP"),
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("文本文件 (*.BMP)|*.BMP|"));	


if(IDOK==dlg.DoModal())
{
	Bmpname.Format("%s",dlg.GetPathName());

	Showpicture(Bmpname);

}		
}
void CShowBmpView::Showpicture(CString Bmpname)
{
	
   	if(State==0)
    {HBITMAP hBitmap = (HBITMAP) LoadImage(NULL, _T(Bmpname), IMAGE_BITMAP,
                    0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
              
              m_bitmap.Attach(hBitmap);     

			  State=1;}

	Invalidate();
	
	
}
