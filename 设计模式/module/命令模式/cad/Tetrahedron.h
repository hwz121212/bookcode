// Tetrahedron.h: interface for the CTetrahedron class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRAHEDRON_H__8BD4836D_1671_4BAA_B8DC_B3094BCCC1F2__INCLUDED_)
#define AFX_TETRAHEDRON_H__8BD4836D_1671_4BAA_B8DC_B3094BCCC1F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CTetrahedron : public CShape  
{
public:
	CTetrahedron();
	virtual ~CTetrahedron();

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

#endif // !defined(AFX_TETRAHEDRON_H__8BD4836D_1671_4BAA_B8DC_B3094BCCC1F2__INCLUDED_)
