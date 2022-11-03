// CircleCommand.h: interface for the CCircleCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLECOMMAND_H__70E7512B_6BE0_46BF_B9B4_C5418C14667C__INCLUDED_)
#define AFX_CIRCLECOMMAND_H__70E7512B_6BE0_46BF_B9B4_C5418C14667C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "cadDoc.h"
#include "Circle.h"

class CCircleCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CCircleCommand(CCadDoc* pDoc);
	virtual ~CCircleCommand();
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_CIRCLECOMMAND_H__70E7512B_6BE0_46BF_B9B4_C5418C14667C__INCLUDED_)
