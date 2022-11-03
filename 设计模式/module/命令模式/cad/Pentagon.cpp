// Pentagon.cpp: implementation of the CPentagon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Pentagon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPentagon::CPentagon()
{

}

CPentagon::~CPentagon()
{

}
void CPentagon::Draw( CDC* pDC )
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
		rc.Y = m_ptEnd.Y ;
	rc.Width = abs(m_ptStart.X - m_ptEnd.X);
	rc.Height = abs(m_ptStart.Y - m_ptEnd.Y);
	
	Point pt[5];

	pt[0].X = rc.X + rc.Width / 2;
	pt[0].Y = rc.Y;

	pt[1].X = rc.X;
	pt[1].Y = rc.Y + rc.Height * 2 / 5;

	pt[2].X = rc.X + rc.Width / 5;
	pt[2].Y = rc.Y + rc.Height;

	pt[3].X = rc.X + rc.Width * 4 / 5;
	pt[3].Y = rc.Y + rc.Height;

	pt[4].X = rc.X + rc.Width;
	pt[4].Y = rc.Y + rc.Height *2 / 5;

	Graphics graphics(pDC->GetSafeHdc());
	Pen pen(Color(255, 0, 255, 255), 2.0f);
	graphics.DrawPolygon(&pen, pt, 5);
	
}

void CPentagon::OnLButtonDown( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetStartPoint(pt);
}

void CPentagon::OnLButtonUp( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CPentagon::OnMouseMove( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CPentagon::SetStartPoint( Point point )
{
	m_ptEnd = m_ptStart = point;
}

void CPentagon::SetEndPoint( Point point )
{	
	m_ptEnd = point;
}

void CPentagon::SetStartAndEndPoint( Point ptStart, Point ptEnd )
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

Rect CPentagon::GetRectBound()
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

Rect CPentagon::GetRoateRect()
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

Rect CPentagon::GetScaleRect()
{
	Rect rc(0, 0, 0, 0);
	return rc;
}

void CPentagon::DrawSelected( Graphics* graphics )
{
	Pen pen(Color(255, 0, 0, 255), 1.0f);
	pen.SetDashStyle(DashStyleDashDot);
	graphics->DrawRectangle(&pen, GetRectBound());
	graphics->DrawEllipse(&pen, GetRoateRect());
}
