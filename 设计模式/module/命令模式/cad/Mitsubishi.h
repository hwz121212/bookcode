// Mitsubishi.h: interface for the CMitsubishi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MITSUBISHI_H__4495D6DF_1342_44CE_BEDC_D8BC3985DDC9__INCLUDED_)
#define AFX_MITSUBISHI_H__4495D6DF_1342_44CE_BEDC_D8BC3985DDC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CMitsubishi : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CMitsubishi();
	virtual ~CMitsubishi();

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

#endif // !defined(AFX_MITSUBISHI_H__4495D6DF_1342_44CE_BEDC_D8BC3985DDC9__INCLUDED_)
