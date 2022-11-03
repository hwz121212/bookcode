// Ellipse.h: interface for the CEllipse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELLIPSE_H__CF89C688_544F_4154_9FC0_C982499C42FE__INCLUDED_)
#define AFX_ELLIPSE_H__CF89C688_544F_4154_9FC0_C982499C42FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CEllipse : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CEllipse();
	virtual ~CEllipse();

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

#endif // !defined(AFX_ELLIPSE_H__CF89C688_544F_4154_9FC0_C982499C42FE__INCLUDED_)
