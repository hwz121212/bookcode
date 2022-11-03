// Sphere.h: interface for the CSphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPHERE_H__2782CDFC_7B1B_47D7_B1CF_A032EBB15F7E__INCLUDED_)
#define AFX_SPHERE_H__2782CDFC_7B1B_47D7_B1CF_A032EBB15F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CSphere : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CSphere();
	virtual ~CSphere();
	
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

#endif // !defined(AFX_SPHERE_H__2782CDFC_7B1B_47D7_B1CF_A032EBB15F7E__INCLUDED_)
