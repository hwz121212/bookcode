// Circle.h: interface for the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__5DBAD88C_A814_4F38_9A02_E655DBDD3985__INCLUDED_)
#define AFX_CIRCLE_H__5DBAD88C_A814_4F38_9A02_E655DBDD3985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CCircle : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CCircle();
	virtual ~CCircle();
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

#endif // !defined(AFX_CIRCLE_H__5DBAD88C_A814_4F38_9A02_E655DBDD3985__INCLUDED_)
