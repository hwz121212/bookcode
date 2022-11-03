// TriangleCommand.h: interface for the CTriangleCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLECOMMAND_H__EE566BB2_A261_49DB_BB35_8FFAAC2AFBC5__INCLUDED_)
#define AFX_TRIANGLECOMMAND_H__EE566BB2_A261_49DB_BB35_8FFAAC2AFBC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"
#include "ICommand.h"
#include "cadDoc.h"
#include "Triangle.h"

class CTriangleCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CTriangleCommand(CCadDoc* pDoc);
	virtual ~CTriangleCommand();
	
	virtual BOOL Execute();
	
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_TRIANGLECOMMAND_H__EE566BB2_A261_49DB_BB35_8FFAAC2AFBC5__INCLUDED_)
