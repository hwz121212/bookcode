// RightTriangleCommand.h: interface for the CRightTriangleCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIGHTTRIANGLECOMMAND_H__22A13B87_E522_4581_AF40_D10C5B6D3F39__INCLUDED_)
#define AFX_RIGHTTRIANGLECOMMAND_H__22A13B87_E522_4581_AF40_D10C5B6D3F39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "cadDoc.h"
#include "RightTriangle.h"

class CRightTriangleCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CRightTriangleCommand(CCadDoc* pDoc);
	virtual ~CRightTriangleCommand();
	virtual BOOL Execute();
	
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_RIGHTTRIANGLECOMMAND_H__22A13B87_E522_4581_AF40_D10C5B6D3F39__INCLUDED_)
