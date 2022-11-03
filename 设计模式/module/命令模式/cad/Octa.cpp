// Octa.cpp: implementation of the COcta class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Octa.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COcta::COcta()
{

}

COcta::~COcta()
{

}

void COcta::Draw( CDC* pDC )
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

	Point pt[6];

	pt[0].X = rc.X + rc.Width / 2;
	pt[0].Y = rc.Y;

	pt[1].X = rc.X;
	pt[1].Y = rc.Y + rc.Height / 2;

	pt[2].X = rc.X + rc.Width / 2;
	pt[2].Y = rc.Y + rc.Height;

	pt[3].X = rc.X + rc.Width;
	pt[3].Y = rc.Y + rc.Height / 2;

	pt[4].X = rc.X + rc.Width / 2 + rc.Width / 2 / 7;
	pt[4].Y = rc.Y + rc.Height / 2 - rc.Height / 2 / 7;

	pt[5].X = rc.X + rc.Width / 2 - rc.Width / 2 / 7;
	pt[5].Y = rc.Y + rc.Height / 2 + rc.Height / 2 / 7;

	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	Pen pen(Color(255, 0, 255, 255), 2.0f);
	pen.SetStartCap(LineCapRound);
	pen.SetEndCap(LineCapRound);
	graphics.DrawLine(&pen, pt[0], pt[1]);
	graphics.DrawLine(&pen, pt[1], pt[2]);
	graphics.DrawLine(&pen, pt[2], pt[3]);
	graphics.DrawLine(&pen, pt[3], pt[0]);

	graphics.DrawLine(&pen, pt[0], pt[5]);
	graphics.DrawLine(&pen, pt[1], pt[5]);
	graphics.DrawLine(&pen, pt[2], pt[5]);
	graphics.DrawLine(&pen, pt[3], pt[5]);

	pen.SetDashStyle(DashStyleDash);

	graphics.DrawLine(&pen, pt[0], pt[4]);
	graphics.DrawLine(&pen, pt[1], pt[4]);
	graphics.DrawLine(&pen, pt[2], pt[4]);
	graphics.DrawLine(&pen, pt[3], pt[4]);

	//SolidBrush brush(Color(255, 0, 0, 255));
	//graphics.FillEllipse(&brush, GetRectBound());
	//DrawSelected(&graphics);
}

void COcta::OnLButtonDown( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetStartPoint(pt);
}

void COcta::OnLButtonUp( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void COcta::OnMouseMove( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

Rect COcta::GetRectBound()
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

void COcta::SetStartPoint( Point point )
{
	m_ptEnd = m_ptStart = point;
}

void COcta::SetEndPoint( Point point )
{
	m_ptEnd = point;
}

void COcta::SetStartAndEndPoint( Point ptStart, Point ptEnd )
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

void COcta::DrawSelected( Graphics* graphics )
{
	Pen pen(Color(255, 0, 0, 255), 1.0f);
	pen.SetDashStyle(DashStyleDashDot);
	graphics->DrawRectangle(&pen, GetRectBound());
	graphics->DrawEllipse(&pen, GetRoateRect());
}

Rect COcta::GetRoateRect()
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

Rect COcta::GetScaleRect()
{
	Rect rc(0, 0, 0, 0);
	return rc;
}