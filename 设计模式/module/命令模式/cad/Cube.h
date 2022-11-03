// Cube.h: interface for the CCube class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBE_H__25416F6A_4566_4DCD_96F5_5641EDD12B80__INCLUDED_)
#define AFX_CUBE_H__25416F6A_4566_4DCD_96F5_5641EDD12B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CCube : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CCube();
	virtual ~CCube();

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

#endif // !defined(AFX_CUBE_H__25416F6A_4566_4DCD_96F5_5641EDD12B80__INCLUDED_)
