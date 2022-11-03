// Octa.h: interface for the COcta class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCTA_H__3EBB63A2_93A0_4A5E_B7E3_8E8DA4211F94__INCLUDED_)
#define AFX_OCTA_H__3EBB63A2_93A0_4A5E_B7E3_8E8DA4211F94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class COcta : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	COcta();
	virtual ~COcta();

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

#endif // !defined(AFX_OCTA_H__3EBB63A2_93A0_4A5E_B7E3_8E8DA4211F94__INCLUDED_)
