// LineCommand.h: interface for the CLineCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINECOMMAND_H__3B8D5767_7D21_4C6C_9A73_4C00C4B0BCF0__INCLUDED_)
#define AFX_LINECOMMAND_H__3B8D5767_7D21_4C6C_9A73_4C00C4B0BCF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "cadDoc.h"
#include "Line.h"
#include "Shape.h"

class CLineCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CLineCommand(CCadDoc* pDoc);
	virtual ~CLineCommand();
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_LINECOMMAND_H__3B8D5767_7D21_4C6C_9A73_4C00C4B0BCF0__INCLUDED_)
