// BitmapView.cpp : implementation of the CBitmapView class
//

#include "stdafx.h"
#include "Bitmap.h"

#include "BitmapDoc.h"
#include "BitmapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapView

IMPLEMENT_DYNCREATE(CBitmapView, CView)

BEGIN_MESSAGE_MAP(CBitmapView, CView)
	//{{AFX_MSG_MAP(CBitmapView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapView construction/destruction

CBitmapView::CBitmapView()
{
	// TODO: add construction code here

}

CBitmapView::~CBitmapView()
{
}

BOOL CBitmapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapView drawing

void CBitmapView::OnDraw(CDC* pDC)
{
	CBitmapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_BITMAP1);
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap=MemDC.SelectObject(&Bitmap);
	BITMAP bm;
	Bitmap.GetObject(sizeof(BITMAP),&bm);
	pDC->BitBlt(130,20,bm.bmWidth,bm.bmHeight,&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pOldBitmap);


}

/////////////////////////////////////////////////////////////////////////////
// CBitmapView printing

BOOL CBitmapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBitmapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBitmapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapView diagnostics

#ifdef _DEBUG
void CBitmapView::AssertValid() const
{
	CView::AssertValid();
}

void CBitmapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitmapDoc* CBitmapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitmapDoc)));
	return (CBitmapDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBitmapView message handlers
