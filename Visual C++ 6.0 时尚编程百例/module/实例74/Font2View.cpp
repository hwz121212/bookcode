// Font2View.cpp : implementation of the CFont2View class
//

#include "stdafx.h"
#include "Font2.h"

#include "Font2Doc.h"
#include "Font2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFont2View

IMPLEMENT_DYNCREATE(CFont2View, CView)

BEGIN_MESSAGE_MAP(CFont2View, CView)
	//{{AFX_MSG_MAP(CFont2View)
	ON_WM_TIMER()
	ON_COMMAND(ID_FONT, OnFont)
	ON_COMMAND(ID_STOP, OnStop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFont2View construction/destruction

CFont2View::CFont2View()
{
	m_dEscapement =0;
	m_dOrientation =0;
	// TODO: add construction code here

}

CFont2View::~CFont2View()
{
}

BOOL CFont2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFont2View drawing

void CFont2View::OnDraw(CDC* pDC)
{
	CFont2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	LOGFONT lf;
	CFont font;
	CFont *oldFont;

	lf.lfHeight = 40;
	lf.lfWidth = 0;
	lf.lfEscapement = m_dEscapement ;
	lf.lfOrientation  = m_dOrientation;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = FALSE;
	lf.lfCharSet = GB2312_CHARSET;
	lf.lfOutPrecision = OUT_STROKE_PRECIS;
	lf.lfClipPrecision = CLIP_STROKE_PRECIS;
	lf.lfQuality = DRAFT_QUALITY;
	lf.lfPitchAndFamily = VARIABLE_PITCH|FF_MODERN;
	strcpy(lf.lfFaceName,"·ÂËÎ_GB2312");

	font.CreateFontIndirect(&lf);
	oldFont=pDC->SelectObject(&font);

	pDC->TextOut(100,100,"VC++6.0°ÙÀý");

	pDC->SelectObject(oldFont);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFont2View printing

BOOL CFont2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFont2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFont2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFont2View diagnostics

#ifdef _DEBUG
void CFont2View::AssertValid() const
{
	CView::AssertValid();
}

void CFont2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFont2Doc* CFont2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFont2Doc)));
	return (CFont2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFont2View message handlers

void CFont2View::OnTimer(UINT_PTR nIDEvent) 
{
	m_dEscapement = m_dEscapement+100;
	m_dOrientation =m_dOrientation+100;
	Invalidate( );

}

void CFont2View::OnFont() 
{
	SetTimer(1,100,NULL);
}

void CFont2View::OnStop() 
{
	KillTimer(1);	
}
