// CubeCommand.h: interface for the CCubeCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBECOMMAND_H__A8A447BE_E25B_4FD1_95E8_DCBBFE789D31__INCLUDED_)
#define AFX_CUBECOMMAND_H__A8A447BE_E25B_4FD1_95E8_DCBBFE789D31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Cube.h"
#include "cadDoc.h"
class CCubeCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CCubeCommand(CCadDoc* pDoc);
	virtual ~CCubeCommand();
	
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_CUBECOMMAND_H__A8A447BE_E25B_4FD1_95E8_DCBBFE789D31__INCLUDED_)
