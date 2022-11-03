// Pentagon.h: interface for the CPentagon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENTAGON_H__C8734D8A_61C1_41FF_8C27_785F5C9BE6BB__INCLUDED_)
#define AFX_PENTAGON_H__C8734D8A_61C1_41FF_8C27_785F5C9BE6BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CPentagon : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CPentagon();
	virtual ~CPentagon();

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

#endif // !defined(AFX_PENTAGON_H__C8734D8A_61C1_41FF_8C27_785F5C9BE6BB__INCLUDED_)
