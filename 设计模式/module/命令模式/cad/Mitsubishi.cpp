// Mitsubishi.cpp: implementation of the CMitsubishi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Mitsubishi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMitsubishi::CMitsubishi()
{

}

CMitsubishi::~CMitsubishi()
{

}

void CMitsubishi::Draw( CDC* pDC )
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

	pt[0].X = rc.X;
	pt[0].Y = rc.Y;

	pt[1].X = rc.X + rc.Width / 2;
	pt[1].Y = rc.Y + rc.Height / 4;

	pt[2].X = rc.X + rc.Width ;
	pt[2].Y = rc.Y;

	pt[3].X = rc.X;
	pt[3].Y = rc.Y + rc.Height * 3 / 4;

	pt[4].X = rc.X + rc.Width / 2;
	pt[4].Y = rc.Y + rc.Height;

	pt[5].X = rc.X + rc.Width;
	pt[5].Y = rc.Y + rc.Height * 3 / 4;



	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	Pen pen(Color(255, 0, 255, 255), 2.0f);
	pen.SetStartCap(LineCapRound);
	pen.SetEndCap(LineCapRound);
	graphics.DrawLine(&pen, pt[0], pt[1]);
	graphics.DrawLine(&pen, pt[1], pt[2]);
	graphics.DrawLine(&pen, pt[2], pt[0]);
	
	graphics.DrawLine(&pen, pt[3], pt[4]);
	graphics.DrawLine(&pen, pt[4], pt[5]);

	graphics.DrawLine(&pen, pt[0], pt[3]);
	graphics.DrawLine(&pen, pt[1], pt[4]);
	graphics.DrawLine(&pen, pt[2], pt[5]);

	pen.SetDashStyle(DashStyleDash);

	graphics.DrawLine(&pen, pt[3], pt[5]);

	//SolidBrush brush(Color(255, 0, 0, 255));
	//graphics.FillEllipse(&brush, GetRectBound());
	//DrawSelected(&graphics);
}

void CMitsubishi::OnLButtonDown( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetStartPoint(pt);
}

void CMitsubishi::OnLButtonUp( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CMitsubishi::OnMouseMove( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

Rect CMitsubishi::GetRectBound()
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

void CMitsubishi::SetStartPoint( Point point )
{
	m_ptEnd = m_ptStart = point;
}

void CMitsubishi::SetEndPoint( Point point )
{
	m_ptEnd = point;
}

void CMitsubishi::SetStartAndEndPoint( Point ptStart, Point ptEnd )
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

void CMitsubishi::DrawSelected( Graphics* graphics )
{
	Pen pen(Color(255, 0, 0, 255), 1.0f);
	pen.SetDashStyle(DashStyleDashDot);
	graphics->DrawRectangle(&pen, GetRectBound());
	graphics->DrawEllipse(&pen, GetRoateRect());
}

Rect CMitsubishi::GetRoateRect()
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

Rect CMitsubishi::GetScaleRect()
{
	Rect rc(0, 0, 0, 0);
	return rc;
}