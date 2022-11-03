// OctaCommand.h: interface for the COctaCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCTACOMMAND_H__FE052D9C_3CD9_4C13_82D6_3579605E458E__INCLUDED_)
#define AFX_OCTACOMMAND_H__FE052D9C_3CD9_4C13_82D6_3579605E458E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Octa.h"
#include "cadDoc.h"

class COctaCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	COctaCommand(CCadDoc* pDoc);
	virtual ~COctaCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_OCTACOMMAND_H__FE052D9C_3CD9_4C13_82D6_3579605E458E__INCLUDED_)
