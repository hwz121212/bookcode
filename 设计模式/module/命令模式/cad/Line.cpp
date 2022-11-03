// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{
	
}

CLine::~CLine()
{

}

void CLine::Draw( CDC* pDC )
{
	Graphics graphics(pDC->GetSafeHdc());
	Pen pen(Color(255, 0, 255, 255), 2.0f);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	graphics.DrawLine(&pen, m_ptStart, m_ptEnd);
	//DrawSelected(&graphics);
}

void CLine::OnLButtonDown( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetStartPoint(pt);
}

void CLine::OnLButtonUp( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CLine::OnMouseMove( UINT nFlags, CPoint point )
{
	Point pt;
	pt.X = point.x;
	pt.Y = point.y;
	SetEndPoint(pt);
}

void CLine::SetStartPoint( Point point )
{
	m_ptEnd = m_ptStart = point;
}

void CLine::SetEndPoint( Point point )
{	
	m_ptEnd = point;
}

void CLine::SetStartAndEndPoint( Point ptStart, Point ptEnd )
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

Rect CLine::GetRectBound()
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

Rect CLine::GetRoateRect()
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

Rect CLine::GetScaleRect()
{
	Rect rc(0, 0, 0, 0);
	return rc;
}

void CLine::DrawSelected( Graphics* graphics )
{
	Pen pen(Color(255, 0, 0, 255), 1.0f);
	pen.SetDashStyle(DashStyleDashDot);
	graphics->DrawRectangle(&pen, GetRectBound());
	graphics->DrawEllipse(&pen, GetRoateRect());
}