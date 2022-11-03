// RectangleCommand.h: interface for the CRectangleCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLECOMMAND_H__7B78EFE6_A0A7_4B9B_B35F_32A5F075C406__INCLUDED_)
#define AFX_RECTANGLECOMMAND_H__7B78EFE6_A0A7_4B9B_B35F_32A5F075C406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"
#include "cadDoc.h"
#include "Rectangle.h"
#include "Shape.h"

class CRectangleCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CRectangleCommand(CCadDoc* pDoc);
	virtual ~CRectangleCommand();
	virtual BOOL Execute();

	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_RECTANGLECOMMAND_H__7B78EFE6_A0A7_4B9B_B35F_32A5F075C406__INCLUDED_)
