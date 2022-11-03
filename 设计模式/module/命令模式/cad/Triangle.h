// Triangle.h: interface for the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLE_H__8F983ECB_A996_4077_A091_30FCB91236F5__INCLUDED_)
#define AFX_TRIANGLE_H__8F983ECB_A996_4077_A091_30FCB91236F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CTriangle : public CShape  
{
// 	Point m_ptStart;
// 	Point m_ptEnd;
public:
	CTriangle();
	virtual ~CTriangle();

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

#endif // !defined(AFX_TRIANGLE_H__8F983ECB_A996_4077_A091_30FCB91236F5__INCLUDED_)
