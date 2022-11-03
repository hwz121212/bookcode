// WavePlayView.cpp : implementation of the CWavePlayView class
//

#include "stdafx.h"
#include "WavePlay.h"

#include "WavePlayDoc.h"
#include "WavePlayView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWavePlayView

IMPLEMENT_DYNCREATE(CWavePlayView, CView)

BEGIN_MESSAGE_MAP(CWavePlayView, CView)
	//{{AFX_MSG_MAP(CWavePlayView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavePlayView construction/destruction

CWavePlayView::CWavePlayView()
{
	// TODO: add construction code here

}

CWavePlayView::~CWavePlayView()
{
}

BOOL CWavePlayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWavePlayView drawing

void CWavePlayView::OnDraw(CDC* pDC)
{
	CWavePlayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect r;
	GetClientRect(&r);
	int x=r.right/3,y=r.bottom/2;
	pDC->TextOut(x,y,"点击鼠标左键或右键会发出丁冬的声音");
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWavePlayView diagnostics

#ifdef _DEBUG
void CWavePlayView::AssertValid() const
{
	CView::AssertValid();
}

void CWavePlayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWavePlayDoc* CWavePlayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWavePlayDoc)));
	return (CWavePlayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWavePlayView message handlers

void CWavePlayView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_wave.Load(IDR_WAVE1,AfxGetInstanceHandle());
	m_wave.Play();
	CView::OnLButtonDown(nFlags, point);
}

void CWavePlayView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_wave.Load(IDR_WAVE2,AfxGetInstanceHandle());
	m_wave.Play();
	CView::OnRButtonDown(nFlags, point);
}
