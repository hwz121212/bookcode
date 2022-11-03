// TestDrawDibView.cpp : implementation of the CTestDrawDibView class
//

#include "stdafx.h"
#include "TestDrawDib.h"

#include "TestDrawDibDoc.h"
#include "TestDrawDibView.h"

#include "vfw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibView

IMPLEMENT_DYNCREATE(CTestDrawDibView, CView)

BEGIN_MESSAGE_MAP(CTestDrawDibView, CView)
	//{{AFX_MSG_MAP(CTestDrawDibView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibView construction/destruction

CTestDrawDibView::CTestDrawDibView()
{
	// TODO: add construction code here

}

CTestDrawDibView::~CTestDrawDibView()
{
}

BOOL CTestDrawDibView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibView drawing

void CTestDrawDibView::OnDraw(CDC* pDC)
{
	CTestDrawDibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	m_DibMem = pDoc->m_Buf;
	if (m_DibMem == NULL)
	{
		//AfxMessageBox("Error in m_DibMem");
		return;
	}
	UINT offset = pDoc->m_Off; 
	int xDst,yDst,dxDst,dyDst,xSrc,ySrc,dxSrc,dySrc;
	LPBITMAPINFOHEADER lpbi;
	LPVOID lpDibMem;
	LPVOID lpbits=NULL;

	// get the Windows width & height
	RECT rect;
	GetClientRect(&rect);
	xDst = yDst = 0;
	dxDst = rect.right - rect.left;
	dyDst = rect.bottom - rect.top;

	// Get Dib info
	xSrc = ySrc =0;
	lpDibMem = GlobalLock(m_DibMem);
	lpbi = (LPBITMAPINFOHEADER)lpDibMem;
	
	dxSrc = lpbi->biWidth; 
    dySrc = lpbi->biHeight; 
    lpbits = (LPSTR)lpDibMem + offset -sizeof(BITMAPFILEHEADER);

	// Draw Dib
	HDC hdc = NULL;
	hdc = pDC->m_hDC;

	/*
	// Using SetDIBToDevice
	int line = SetDIBitsToDevice(hdc,
					xDst,
					yDst,
					dxSrc,
					dySrc,
					xSrc,
					ySrc,
					0,
					dySrc,
					lpdib,//lpbits,
					(LPBITMAPINFO)lpbi,
					DIB_RGB_COLORS);
	if(0 == line)
	{
		AfxMessageBox("Error in SetDIBsToDevice");
	}
	*/
/*
	// Using StretchDIBits
	int line = StretchDIBits(hdc,
					xDst,
					yDst,
					dxDst,
					dyDst,
					xSrc,
					ySrc,
					dxSrc,
					dySrc,					
					lpbits,
					(LPBITMAPINFO)lpbi,
					DIB_RGB_COLORS,
					SRCCOPY);
	if(0 == line)
	{
		AfxMessageBox("Error in SetDIBsToDevice");
	}
*/	

	// Using DrawDib

	// Set Dawing flag
	UINT wFlags;
	//wFlags = DDF_DONTDRAW;
	wFlags = DDF_NOTKEYFRAME;

	HDRAWDIB hdd = DrawDibOpen();
	if (hdd != NULL) 
	{
		//DrawDibBegin(hdd,hdc,dxDst,dyDst,lpbi,dxSrc,dySrc,DDF_JUSTDRAWIT);
		BOOL Suc = TRUE;
		Suc = DrawDibDraw(hdd,hdc,xDst,yDst,dxDst,dyDst,lpbi,lpbits,
					xSrc,ySrc,dxSrc,dySrc,wFlags);
		if(Suc == FALSE) AfxMessageBox("DrawDib Failed");
		/*	
		DRAWDIBTIME time;
		DrawDibTime(hdd ,&time);
		char buf[256];
		sprintf(buf,"Count %d\nDraw %d\nDecompress %d\nDither %d\nStretch %d\nBlt %d\nSetDIBits %d\n",
			time.timeCount,time.timeDraw,time.timeDecompress,time.timeDither,
			time.timeStretch,time.timeBlt,time.timeSetDIBits); 
		AfxMessageBox(buf);
	*/
		//DrawDibEnd(hdd);
		
		DrawDibClose(hdd);
	}
	else
		AfxMessageBox("Error in DrawDibOpen");

	
	GlobalUnlock(m_DibMem);
}

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibView printing

BOOL CTestDrawDibView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestDrawDibView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestDrawDibView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibView diagnostics

#ifdef _DEBUG
void CTestDrawDibView::AssertValid() const
{
	CView::AssertValid();
}

void CTestDrawDibView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDrawDibDoc* CTestDrawDibView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDrawDibDoc)));
	return (CTestDrawDibDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibView message handlers
