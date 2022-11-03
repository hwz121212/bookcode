// Cone.h: interface for the CCone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONE_H__B3385C12_9D64_4EAF_97C4_3C30C0582D04__INCLUDED_)
#define AFX_CONE_H__B3385C12_9D64_4EAF_97C4_3C30C0582D04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CCone : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CCone();
	virtual ~CCone();
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

#endif // !defined(AFX_CONE_H__B3385C12_9D64_4EAF_97C4_3C30C0582D04__INCLUDED_)
