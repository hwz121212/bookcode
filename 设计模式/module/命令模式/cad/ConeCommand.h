// ConeCommand.h: interface for the CConeCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONECOMMAND_H__B424499B_8056_4AE7_939B_691ACB32138F__INCLUDED_)
#define AFX_CONECOMMAND_H__B424499B_8056_4AE7_939B_691ACB32138F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Cone.h"
#include "cadDoc.h"

class CConeCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CConeCommand(CCadDoc* pDoc);
	virtual ~CConeCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_CONECOMMAND_H__B424499B_8056_4AE7_939B_691ACB32138F__INCLUDED_)
