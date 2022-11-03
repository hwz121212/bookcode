// Ryotai.cpp: implementation of the CRyotai class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Ryotai.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRyotai::CRyotai()
{

}

CRyotai::~CRyotai()
{

}
void CRyotai::Draw( CDC* pDC )
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

	Point pt[8];

	pt[0].X = rc.X + rc.Width / 3;
	pt[0].Y = rc.Y;

	pt[1].X = rc.X + rc.Width / 3 / 3;
	pt[1].Y = rc.Y + rc.Height / 8;

	pt[2].X = rc.X + rc.Width / 3 + rc.Width / 3  / 3;
	pt[2].Y = rc.Y + rc.Height / 8;

	pt[3].X = rc.X + rc.Width * 2 / 3;
	pt[3].Y = rc.Y;

	pt[4].X = rc.X + rc.Width / 4;
	pt[4].Y = rc.Y + rc.Height * 3 / 4;

	pt[5].X = rc.X;
	pt[5].Y = rc.Y + rc.Height;

	pt[6].X = rc.X + rc.Width * 3 / 4;
	pt[6].Y = rc.Y + rc.Height;

	pt[7].X = rc.X + rc.Width;
	pt[7].Y = rc.Y + rc.Height * 3 / 4;

	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	Pen pen(Color(255, 0, 255, 255), 2.0f);
	pen.SetStartCap(LineCapRound);
	pen.SetEndCap(LineCapRound);
	graphics.DrawLine(&pen, pt[0], pt[1]);
	graphics.DrawLine(&pen, pt[1], pt[2]);
	graphics.DrawLine(&pen, pt[2], pt[3]);
	graphics.DrawLine(&pen, pt[3], pt[0]);
	
	graphics.DrawLine(&pen, pt[5], pt[6]);
	graphics.DrawLine(&pen, pt[6], pt[7]);

	graphics.DrawLine(&pen, pt[1], pt[5]);
	graphics.DrawLine(&pen, pt[2], pt[6]);
	graphics.DrawLine(&pen, pt[7], pt[3]);

	pen.SetDashStyle(DashStyleDash);

	graphics.DrawLine(&pen, pt[0], pt[4]);
	graphics.DrawLine(&pen, pt[4], pt[5]);
	graphics.DrawLine(&pen, pt[7], pt[4]);

	//SolidBrush brush(Color(255, 0, 0, 255));
	//graphics.FillEllipse(&brush, GetRectBound());
	//DrawSelected(&graphics);
}

void CRyotai::OnLButtonDown( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetStartPoint(pt);
}

void CRyotai::OnLButtonUp( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CRyotai::OnMouseMove( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

Rect CRyotai::GetRectBound()
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

void CRyotai::SetStartPoint( Point point )
{
	m_ptEnd = m_ptStart = point;
}

void CRyotai::SetEndPoint( Point point )
{
	m_ptEnd = point;
}

void CRyotai::SetStartAndEndPoint( Point ptStart, Point ptEnd )
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

void CRyotai::DrawSelected( Graphics* graphics )
{
	Pen pen(Color(255, 0, 0, 255), 1.0f);
	pen.SetDashStyle(DashStyleDashDot);
	graphics->DrawRectangle(&pen, GetRectBound());
	graphics->DrawEllipse(&pen, GetRoateRect());
}

Rect CRyotai::GetRoateRect()
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

Rect CRyotai::GetScaleRect()
{
	Rect rc(0, 0, 0, 0);
	return rc;
}