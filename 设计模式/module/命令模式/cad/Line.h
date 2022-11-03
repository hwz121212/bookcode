// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__6CF7A4F5_50FC_4177_81AF_E2611FDB927A__INCLUDED_)
#define AFX_LINE_H__6CF7A4F5_50FC_4177_81AF_E2611FDB927A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CLine : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:

	CLine();
	virtual ~CLine();

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

#endif // !defined(AFX_LINE_H__6CF7A4F5_50FC_4177_81AF_E2611FDB927A__INCLUDED_)
