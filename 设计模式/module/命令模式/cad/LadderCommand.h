// LadderCommand.h: interface for the CLadderCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LADDERCOMMAND_H__A825ECF0_88BE_4519_868A_767D6DA1B45A__INCLUDED_)
#define AFX_LADDERCOMMAND_H__A825ECF0_88BE_4519_868A_767D6DA1B45A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "cadDoc.h"
#include "Ladder.h"
class CLadderCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CLadderCommand(CCadDoc* pDoc);
	virtual ~CLadderCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_LADDERCOMMAND_H__A825ECF0_88BE_4519_868A_767D6DA1B45A__INCLUDED_)
