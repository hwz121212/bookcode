// Pentagram.h: interface for the CPentagram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENTAGRAM_H__A48BD894_4203_42CD_AE19_F0D8C2CD4F6C__INCLUDED_)
#define AFX_PENTAGRAM_H__A48BD894_4203_42CD_AE19_F0D8C2CD4F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CPentagram : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	int GetIntersect(Point L11, Point L12, Point L21, Point L22, Point& inter);
	CPentagram();
	virtual ~CPentagram();
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

#endif // !defined(AFX_PENTAGRAM_H__A48BD894_4203_42CD_AE19_F0D8C2CD4F6C__INCLUDED_)
