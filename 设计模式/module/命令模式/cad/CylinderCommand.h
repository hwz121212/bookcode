// CylinderCommand.h: interface for the CCylinderCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYLINDERCOMMAND_H__9879123D_2CC6_4F93_8B92_FE0EE252AFE1__INCLUDED_)
#define AFX_CYLINDERCOMMAND_H__9879123D_2CC6_4F93_8B92_FE0EE252AFE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Cylinder.h"
#include "cadDoc.h"

class CCylinderCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CCylinderCommand(CCadDoc* pDoc);
	virtual ~CCylinderCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_CYLINDERCOMMAND_H__9879123D_2CC6_4F93_8B92_FE0EE252AFE1__INCLUDED_)
