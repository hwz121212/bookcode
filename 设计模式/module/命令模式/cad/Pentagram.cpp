// Pentagram.cpp: implementation of the CPentagram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Pentagram.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPentagram::CPentagram()
{

}

CPentagram::~CPentagram()
{

}
void CPentagram::Draw( CDC* pDC )
{
	Rect rc;
	if (m_ptStart.X > m_ptEnd.X)
	{
		rc.X = m_ptEnd.X;
	}
	else
		rc.X = m_ptStart.X ;
	if (m_ptStart.Y < m_ptEnd.Y)
	{
		rc.Y = m_ptStart.Y ;
	}
	else
		rc.Y = m_ptEnd.Y;
	rc.Width = abs(m_ptStart.X - m_ptEnd.X);
	rc.Height = abs(m_ptStart.Y - m_ptEnd.Y);
	
	Point pt[10];

	pt[0].X = rc.X + rc.Width / 2;
	pt[0].Y = rc.Y;

	pt[2].X = rc.X;
	pt[2].Y = rc.Y + rc.Height * 2 / 5;

	pt[4].X = rc.X + rc.Width / 5;
	pt[4].Y = rc.Y + rc.Height;

	pt[6].X = rc.X + rc.Width * 4 / 5;
	pt[6].Y = rc.Y + rc.Height;

	pt[8].X = rc.X + rc.Width;
	pt[8].Y = rc.Y + rc.Height * 2 / 5;



	GetIntersect(pt[0], pt[4], pt[2], pt[8], pt[1]);
	GetIntersect(pt[0], pt[4], pt[2], pt[6], pt[3]);
	GetIntersect(pt[2], pt[6], pt[4], pt[8], pt[5]);
	GetIntersect(pt[0], pt[6], pt[4], pt[8], pt[7]);
	GetIntersect(pt[0], pt[6], pt[2], pt[8], pt[9]);

	for (int i = 0; i < 10; i++)
	{
		if (pt[i].X == 0)
		{
			return;
		}
	}

	Graphics graphics(pDC->GetSafeHdc());
	Pen pen(Color(255, 0, 255, 255), 2.0f);
	graphics.DrawPolygon(&pen, pt, 10);


	
}

void CPentagram::OnLButtonDown( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetStartPoint(pt);
}

void CPentagram::OnLButtonUp( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CPentagram::OnMouseMove( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CPentagram::SetStartPoint( Point point )
{
	m_ptEnd = m_ptStart = point;
}

void CPentagram::SetEndPoint( Point point )
{	
	m_ptEnd = point;
}

void CPentagram::SetStartAndEndPoint( Point ptStart, Point ptEnd )
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

Rect CPentagram::GetRectBound()
{
	Rect rc;
	if (m_ptStart.X > m_ptEnd.X)
	{
		rc.X = m_ptEnd.X - 5;
	}
	else
		rc.X = m_ptStart.X - 5;
	if (m_ptStart.Y < m_ptEnd.Y)
	{
		rc.Y = m_ptStart.Y - 5;
	}
	else
		rc.Y = m_ptEnd.Y - 5;
	rc.Width = abs(m_ptStart.X - m_ptEnd.X) + 10;
	rc.Height = abs(m_ptStart.Y - m_ptEnd.Y) + 10;
	
	return rc;
}

Rect CPentagram::GetRoateRect()
{
	Rect rc;
	rc = GetRectBound();
	Rect rcRoate;
	rcRoate.X = rc.X + rc.Width / 2;
	rcRoate.Y = rc.Y - 20;
	rcRoate.Width = 15;
	rcRoate.Height = 15;
	return rcRoate;
}

Rect CPentagram::GetScaleRect()
{
	Rect rc(0, 0, 0, 0);
	return rc;
}

void CPentagram::DrawSelected( Graphics* graphics )
{
	Pen pen(Color(255, 0, 0, 255), 1.0f);
	pen.SetDashStyle(DashStyleDashDot);
	graphics->DrawRectangle(&pen, GetRectBound());
	graphics->DrawEllipse(&pen, GetRoateRect());
}

int CPentagram::GetIntersect(Point L11, Point L12, Point L21, Point L22, Point& inter)
{   
	float a1=L12.Y - L11.Y;   
	float b1=L11.X - L12.X;   
	float c1=L11.X * L12.Y - L12.X * L11.Y;   
 
	float a2=L22.Y-L21.Y;   
	float b2=L21.X-L22.X;   
	float c2=L21.X*L22.Y-L22.X*L21.Y;   
    
	float detab = a1 * b2 - a2 * b1;   
	if(detab == 0)   
	{   
		float r;   
		if(a2 != 0)   
			r = a1 / a2;   
		else   
			r = b1 / b2;   
		
		if(c1 == 0 && c2 == 0)   
			return 2;   
		if(r == c1 / c2)   
			return 2;   
		else   
			return 0;   
	}   
    
	inter.X = (c1 * b2 - c2 * b1) / detab;   
	inter.Y = (a1 * c2 - a2 * c1) / detab;   
	return 1;   
  }