// RightTriangle.h: interface for the CRightTriangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIGHTTRIANGLE_H__AC49D37E_7C34_4577_87D0_619F80EB86B1__INCLUDED_)
#define AFX_RIGHTTRIANGLE_H__AC49D37E_7C34_4577_87D0_619F80EB86B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CRightTriangle : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CRightTriangle();
	virtual ~CRightTriangle();

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

#endif // !defined(AFX_RIGHTTRIANGLE_H__AC49D37E_7C34_4577_87D0_619F80EB86B1__INCLUDED_)
