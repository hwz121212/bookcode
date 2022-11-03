// PentagonCommand.h: interface for the CPentagonCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENTAGONCOMMAND_H__A8E2BC90_741B_4983_B0A9_22BE3FCC39AB__INCLUDED_)
#define AFX_PENTAGONCOMMAND_H__A8E2BC90_741B_4983_B0A9_22BE3FCC39AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Shape.h"
#include "ICommand.h"
#include "cadDoc.h"
#include "Pentagon.h"

class CPentagonCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CPentagonCommand(CCadDoc* pDoc);
	virtual ~CPentagonCommand();
	
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_PENTAGONCOMMAND_H__A8E2BC90_741B_4983_B0A9_22BE3FCC39AB__INCLUDED_)
