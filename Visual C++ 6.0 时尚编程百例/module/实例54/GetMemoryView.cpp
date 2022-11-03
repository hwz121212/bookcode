// GetMemoryView.cpp : implementation of the CGetMemoryView class
//

#include "stdafx.h"
#include "GetMemory.h"

#include "GetMemoryDoc.h"
#include "GetMemoryView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define PI 3.1415
#define RADIUS 900
/////////////////////////////////////////////////////////////////////////////
// CGetMemoryView

IMPLEMENT_DYNCREATE(CGetMemoryView, CView)

BEGIN_MESSAGE_MAP(CGetMemoryView, CView)
	//{{AFX_MSG_MAP(CGetMemoryView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetMemoryView construction/destruction

CGetMemoryView::CGetMemoryView()
{
	// TODO: add construction code here

}

CGetMemoryView::~CGetMemoryView()
{
}

BOOL CGetMemoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGetMemoryView drawing

void CGetMemoryView::OnDraw(CDC* pDC)
{
	CGetMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString str;
	int x,y;
	double dFree,dUse; 
	CRect rect;
	CPen Pen;
	CBrush Brush;
	Brush.CreateSolidBrush(RGB(255,0,0));
	Pen.CreatePen(PS_SOLID, 100,RGB(255,0,0));
    pDC->SelectObject(&Pen);
	pDC->SelectObject(&Brush);
	::GlobalMemoryStatus(&mem);
	MemTotal=mem.dwTotalPhys;
	Memfree=mem.dwAvailPhys;
    GetClientRect( &rect );
    pDC->SetMapMode( MM_ISOTROPIC );
    pDC->SetWindowExt( RADIUS+100, RADIUS+100 );
    pDC->SetViewportExt( rect.right/2, -rect.bottom/2 );
    pDC->SetViewportOrg( rect.right/2, rect.bottom/2 );
	dFree = (double) (PI*2 * Memfree/MemTotal);
    dUse  = (double) PI*2 - dFree;

  
    x = -(int) (sin( dUse ) * RADIUS);
    y =  (int) (cos( dUse ) * RADIUS);
    pDC->Pie( -RADIUS, RADIUS, RADIUS, -RADIUS, 0, RADIUS, x, y );
	GetMemoryStr(&str,MemTotal,"×Ü¹²");

	pDC->TextOut(300,300,str);

	GetMemoryStr(&str,Memfree,"Ê£Óà");
	pDC->TextOut(100,200,str);

}

void CGetMemoryView::GetMemoryStr(CString *str,double m_mem,PCSTR strTail)
{

    char    m_ch = 'K';                 

    m_mem /= 1024;
    if (m_mem > 1024)                       
    {                                  
        m_mem  /= 1024;                  
        m_ch  = 'M';                   
    }
    str->Format( "%.2f %c%s%s", m_mem, m_ch, "b ", strTail );
}


#ifdef _DEBUG
void CGetMemoryView::AssertValid() const
{
	CView::AssertValid();
}

void CGetMemoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGetMemoryDoc* CGetMemoryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGetMemoryDoc)));
	return (CGetMemoryDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGetMemoryView message handlers
