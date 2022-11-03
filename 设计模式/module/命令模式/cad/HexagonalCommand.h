// HexagonalCommand.h: interface for the CHexagonalCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXAGONALCOMMAND_H__DDF33961_49B8_4640_888C_63DEE85934DF__INCLUDED_)
#define AFX_HEXAGONALCOMMAND_H__DDF33961_49B8_4640_888C_63DEE85934DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "cadDoc.h"
#include "Hexagonal.h"

class CHexagonalCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CHexagonalCommand(CCadDoc* pDoc);
	virtual ~CHexagonalCommand();
	
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_HEXAGONALCOMMAND_H__DDF33961_49B8_4640_888C_63DEE85934DF__INCLUDED_)
