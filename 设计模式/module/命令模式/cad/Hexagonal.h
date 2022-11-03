// Hexagonal.h: interface for the CHexagonal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXAGONAL_H__22249583_BB0A_4576_A5D9_109EB5A7F7CB__INCLUDED_)
#define AFX_HEXAGONAL_H__22249583_BB0A_4576_A5D9_109EB5A7F7CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CHexagonal : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CHexagonal();
	virtual ~CHexagonal();
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

#endif // !defined(AFX_HEXAGONAL_H__22249583_BB0A_4576_A5D9_109EB5A7F7CB__INCLUDED_)
