// DiamondCommand.h: interface for the CDiamondCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAMONDCOMMAND_H__B7C5CE38_78CF_4A02_AC61_9BF944318412__INCLUDED_)
#define AFX_DIAMONDCOMMAND_H__B7C5CE38_78CF_4A02_AC61_9BF944318412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "cadDoc.h"
#include "Diamond.h"

class CDiamondCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CDiamondCommand(CCadDoc* pDoc);
	virtual ~CDiamondCommand();

	virtual BOOL Execute();
	
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_DIAMONDCOMMAND_H__B7C5CE38_78CF_4A02_AC61_9BF944318412__INCLUDED_)
