// Ladder.h: interface for the CLadder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LADDER_H__0180A11F_0F98_4F10_9BEB_722FCB1DBD2E__INCLUDED_)
#define AFX_LADDER_H__0180A11F_0F98_4F10_9BEB_722FCB1DBD2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CLadder : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CLadder();
	virtual ~CLadder();

	virtual void Draw(CDC* pDC);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual Rect GetRectBound();
protected:
	void SetStartPoint(Point point);
	void SetEndPoint(Point point);
	void SetStartAndEndPoint(Point ptStart, Point ptEnd);
	void DrawSelected(Graphics* graphics);
	Rect GetRoateRect();
	Rect GetScaleRect();
};

#endif // !defined(AFX_LADDER_H__0180A11F_0F98_4F10_9BEB_722FCB1DBD2E__INCLUDED_)
