// Diamond.h: interface for the CDiamond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAMOND_H__2851E385_C8CC_4E86_9DB5_E446A600F239__INCLUDED_)
#define AFX_DIAMOND_H__2851E385_C8CC_4E86_9DB5_E446A600F239__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CDiamond : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CDiamond();
	virtual ~CDiamond();

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

#endif // !defined(AFX_DIAMOND_H__2851E385_C8CC_4E86_9DB5_E446A600F239__INCLUDED_)
