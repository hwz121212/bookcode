// ArcCommand.h: interface for the CArcCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCCOMMAND_H__FA06BB0A_CF6F_4756_BA41_9302B49BC34B__INCLUDED_)
#define AFX_ARCCOMMAND_H__FA06BB0A_CF6F_4756_BA41_9302B49BC34B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Arc.h"
#include "cadDoc.h"

class CArcCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CArcCommand(CCadDoc* pDoc);
	virtual ~CArcCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_ARCCOMMAND_H__FA06BB0A_CF6F_4756_BA41_9302B49BC34B__INCLUDED_)
