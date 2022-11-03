// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__6B7846BD_B39C_4F0D_BB93_A02839C86EBD__INCLUDED_)
#define AFX_ARC_H__6B7846BD_B39C_4F0D_BB93_A02839C86EBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CArc : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CArc();
	virtual ~CArc();

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

#endif // !defined(AFX_ARC_H__6B7846BD_B39C_4F0D_BB93_A02839C86EBD__INCLUDED_)
