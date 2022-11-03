// Parallelogram.h: interface for the CParallelogram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARALLELOGRAM_H__C54D0EAE_2A85_4462_8092_AD599C023A91__INCLUDED_)
#define AFX_PARALLELOGRAM_H__C54D0EAE_2A85_4462_8092_AD599C023A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CParallelogram : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CParallelogram();
	virtual ~CParallelogram();
	
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

#endif // !defined(AFX_PARALLELOGRAM_H__C54D0EAE_2A85_4462_8092_AD599C023A91__INCLUDED_)
