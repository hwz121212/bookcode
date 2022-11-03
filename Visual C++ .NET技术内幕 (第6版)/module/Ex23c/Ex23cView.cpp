// Ex23cView.cpp : implementation of the CEx23cView class
//

#include "stdafx.h"
#include "Ex23c.h"

#include "Alarm.h"

#include "Ex23cDoc.h"
#include "Ex23cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx23cView

const int CEx23cView::nX[] = {
   0, 105, 208, 309, 407, 500, 588, 669, 743, 809, 866, 914, 
   951, 978, 995, 1000, 995, 978, 951, 914, 866, 809, 743, 669, 
   588, 500, 407, 309, 208, 105, 0, -104, -207, -308, -406, -499, 
   -587, -668, -742, -808, -865, -913, -950, -977, -994, -999, -994, -977, 
   -950, -913, -865, -808, -742, -668, -587, -499, -406, -308, -207, -104 }; 
const int CEx23cView::nY[] = {
   999, 994, 978, 951, 913, 866, 809, 743, 669, 587, 499, 406, 
   309, 207, 104, 0, -104, -207, -309, -406, -499, -587, -669, -743, 
   -809, -866, -913, -951, -978, -994, -999, -994, -978, -951, -913, -866, 
   -809, -743, -669, -587, -500, -406, -309, -207, -104, 0, 104, 207, 
   309, 406, 499, 587, 669, 743, 809, 866, 913, 951, 978, 994 }; 


IMPLEMENT_DYNCREATE(CEx23cView, CView)

BEGIN_MESSAGE_MAP(CEx23cView, CView)
    ON_WM_CREATE()
END_MESSAGE_MAP()

// CEx23cView construction/destruction

CEx23cView::CEx23cView()
{
	// TODO: add construction code here

}

CEx23cView::~CEx23cView()
{
}

BOOL CEx23cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx23cView drawing

void CEx23cView::OnDraw(CDC* pDC)
{
	CEx23cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
   CRect rectClient;
   CPen pen0(PS_SOLID, 0, (COLORREF) 0);
   CPen pen1(PS_SOLID, 20, (COLORREF) 0);
   CPen pen2(PS_SOLID, 30, (COLORREF) 0);
   int i, j, n, m, nS, nM, nH;
   CSize sz;
   pDC->SetMapMode(MM_ISOTROPIC);
   GetClientRect(rectClient);
   pDC->SetWindowExt(2400, 2400);
   pDC->SetViewportExt(rectClient.right, -rectClient.bottom);
   pDC->SetViewportOrg(rectClient.right / 2, rectClient.bottom / 2);
   pDC->SelectObject(&m_font);
   pDC->SelectObject(&pen0);
   for(i = 0; i < 60; i++) { // second/minute ticks
      pDC->MoveTo(nX[i], nY[i]);
      pDC->LineTo(nX[i] * 9 / 10, nY[i] * 9 / 10);
   }
   pDC->SelectObject(&pen1);
   for(i = 0; i < 12; i++) { // hour ticks
      j = i * 5;
      pDC->MoveTo(nX[j], nY[j]);
      pDC->LineTo(nX[j] * 8 / 10, nY[j] * 8 / 10);
   }
   for(i = 0; i < 4; i++) { // figures
      j = i * 15;
      sz = pDC->GetTextExtent(pDoc->m_strFigure[i], pDoc->m_strFigure[i].GetLength());
      n  = nX[j] * 10 / 9 - sz.cx / 2;
      m  = nY[j] * 10 / 9 + sz.cy / 2;
      pDC->TextOut(n, m, pDoc->m_strFigure[i]);
   }

   // draw the clock hands
   COleDateTime dt = pDoc->m_time;
   nH = dt.GetHour();
   nM = dt.GetMinute();
   nS = dt.GetSecond();
   pDC->SelectObject(&pen0);
   i = nS;
   pDC->MoveTo(0, 0);
   pDC->LineTo(nX[i], nY[i]); // seconds
   
   pDC->SelectObject(&pen1);
   i = nM;
   pDC->MoveTo(0, 0);
   pDC->LineTo(nX[i] * 8 / 10, nY[i] * 8 / 10); // minutes

   pDC->SelectObject(&pen2);
   i = nH * 5;
   i = (i % 60) + nM / 12;
   pDC->MoveTo(0, 0);
   pDC->LineTo(nX[i] * 6 / 10, nY[i] * 6 / 10); // hours

   pDC->SelectStockObject(BLACK_PEN);
   CAlarm* pAlarm;
   if((pAlarm = pDoc->m_pAlarm) != NULL) {
      COleDateTime dt = pAlarm->m_time;
      nH = dt.GetHour();
      nM = dt.GetMinute();
      nS = dt.GetSecond();
	  TRACE("dt = %f, nH = %d, nM = %d, nS = %d\n", dt.m_dt, nH, nM, nS);
      i = nH * 5;
      i = (i % 60) + nM / 12;
      pDC->TextOut(nX[i] * 8 / 10, nY[i] * 8 / 10, "A"); // alarm
   }
}


// CEx23cView diagnostics

#ifdef _DEBUG
void CEx23cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx23cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx23cDoc* CEx23cView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx23cDoc)));
	return (CEx23cDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx23cView message handlers

int CEx23cView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CView::OnCreate(lpCreateStruct) == -1)
      return -1;
   m_font.CreateFont(150, 0, 0, 0, 400, FALSE, FALSE,
               0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
               CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
               DEFAULT_PITCH | FF_SWISS,
               "Arial");               
   return 0;
}
