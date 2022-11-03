// RyotaiCommand.h: interface for the CRyotaiCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RYOTAICOMMAND_H__8ECD021B_A7D6_4899_9BEC_1A44701986EF__INCLUDED_)
#define AFX_RYOTAICOMMAND_H__8ECD021B_A7D6_4899_9BEC_1A44701986EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Ryotai.h"
#include "cadDoc.h"

class CRyotaiCommand : public CICommand  
{
	CCadDoc* m_pDoc;
	CShape* m_pShape;
public:
	CRyotaiCommand(CCadDoc* pDoc);
	virtual ~CRyotaiCommand();
	
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_RYOTAICOMMAND_H__8ECD021B_A7D6_4899_9BEC_1A44701986EF__INCLUDED_)
