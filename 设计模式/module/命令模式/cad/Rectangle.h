// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE_H__419EF3FB_89FF_46FA_99E2_0A88E341DC4B__INCLUDED_)
#define AFX_RECTANGLE_H__419EF3FB_89FF_46FA_99E2_0A88E341DC4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CRectangle : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CRectangle();
	virtual ~CRectangle();

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

#endif // !defined(AFX_RECTANGLE_H__419EF3FB_89FF_46FA_99E2_0A88E341DC4B__INCLUDED_)
