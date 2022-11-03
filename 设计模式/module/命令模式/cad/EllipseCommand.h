// EllipseCommand.h: interface for the CEllipseCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELLIPSECOMMAND_H__19C36808_3078_4915_B06C_D7C6F5EF5245__INCLUDED_)
#define AFX_ELLIPSECOMMAND_H__19C36808_3078_4915_B06C_D7C6F5EF5245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Shape.h"
#include "cadDoc.h"
#include "Ellipse.h"

class CEllipseCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CEllipseCommand(CCadDoc* pDoc);
	virtual ~CEllipseCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_ELLIPSECOMMAND_H__19C36808_3078_4915_B06C_D7C6F5EF5245__INCLUDED_)
