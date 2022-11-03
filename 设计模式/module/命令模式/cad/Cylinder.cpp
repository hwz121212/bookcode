// Cylinder.cpp: implementation of the CCylinder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Cylinder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCylinder::CCylinder()
{

}

CCylinder::~CCylinder()
{

}
void CCylinder::Draw( CDC* pDC )
{
	Rect rc;
	if (m_ptStart.X > m_ptEnd.X)
	{
		rc.X = m_ptEnd.X;
	}
	else
		rc.X = m_ptStart.X;
	if (m_ptStart.Y < m_ptEnd.Y)
	{
		rc.Y = m_ptStart.Y;
	}
	else
		rc.Y = m_ptEnd.Y;
	rc.Width = abs(m_ptStart.X - m_ptEnd.X);
	rc.Height = abs(m_ptStart.Y - m_ptEnd.Y);

	Point pt[4];

	pt[0].X = rc.X;
	pt[0].Y = rc.Y + rc.Height / 8;

	pt[1].X = rc.X + rc.Width;
	pt[1].Y = rc.Y + rc.Height / 8;

	pt[2].X = rc.X;
	pt[2].Y = rc.Y + rc.Height * 7 / 8;

	pt[3].X = rc.X + rc.Width;
	pt[3].Y = rc.Y + rc.Height * 7 / 8;

	Rect rcTop(rc.X, rc.Y, rc.Width, rc.Height / 4);
	Rect rcBottom(rc.X, rc.Y + rc.Height * 3 / 4, rc.Width, rc.Height / 4);
	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	Pen pen(Color(255, 0, 255, 255), 2.0f);
	pen.SetStartCap(LineCapRound);
	pen.SetEndCap(LineCapRound);
	
	graphics.DrawEllipse(&pen, rcTop);
	
	graphics.DrawLine(&pen, pt[0], pt[2]);
	graphics.DrawLine(&pen, pt[1], pt[3]);
	REAL r1 = 0.0;
	REAL r2 = 180;
	graphics.DrawArc(&pen, rcBottom, r1, r2);
	pen.SetDashStyle(DashStyleDash);
	r1 = 180;
	graphics.DrawArc(&pen, rcBottom, r1, r2);



	//SolidBrush brush(Color(255, 0, 0, 255));
	//graphics.FillEllipse(&brush, GetRectBound());
	//DrawSelected(&graphics);
}

void CCylinder::OnLButtonDown( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetStartPoint(pt);
}

void CCylinder::OnLButtonUp( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CCylinder::OnMouseMove( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

Rect CCylinder::GetRectBound()
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

void CCylinder::SetStartPoint( Point point )
{
	m_ptEnd = m_ptStart = point;
}

void CCylinder::SetEndPoint( Point point )
{
	m_ptEnd = point;
}

void CCylinder::SetStartAndEndPoint( Point ptStart, Point ptEnd )
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

void CCylinder::DrawSelected( Graphics* graphics )
{
	Pen pen(Color(255, 0, 0, 255), 1.0f);
	pen.SetDashStyle(DashStyleDashDot);
	graphics->DrawRectangle(&pen, GetRectBound());
	graphics->DrawEllipse(&pen, GetRoateRect());
}

Rect CCylinder::GetRoateRect()
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

Rect CCylinder::GetScaleRect()
{
	Rect rc(0, 0, 0, 0);
	return rc;
}