// Cylinder.h: interface for the CCylinder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYLINDER_H__8F37C40E_3A1D_4F2A_BF3A_7DD2EC60EC83__INCLUDED_)
#define AFX_CYLINDER_H__8F37C40E_3A1D_4F2A_BF3A_7DD2EC60EC83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CCylinder : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CCylinder();
	virtual ~CCylinder();

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

#endif // !defined(AFX_CYLINDER_H__8F37C40E_3A1D_4F2A_BF3A_7DD2EC60EC83__INCLUDED_)
