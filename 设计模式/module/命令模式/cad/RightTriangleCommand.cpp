// RightTriangleCommand.cpp: implementation of the CRightTriangleCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "RightTriangleCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRightTriangleCommand::CRightTriangleCommand(CCadDoc* pDoc)
{
	m_pDoc = pDoc;
	m_pShape = new CRightTriangle;
}

CRightTriangleCommand::~CRightTriangleCommand()
{

}

BOOL CRightTriangleCommand::Execute()
{
	m_pDoc->AddShape(m_pShape);
	return TRUE;
}

BOOL CRightTriangleCommand::Unexecute()
{
	m_pDoc->RemoveShape(m_pShape);
	return TRUE;
}

void CRightTriangleCommand::OnLButtonDown( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonDown(nFlags, point);
}

void CRightTriangleCommand::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonUp(nFlags, point);
}

void CRightTriangleCommand::OnMouseMove( UINT nFlags, CPoint point )
{
	m_pShape->OnMouseMove(nFlags, point);
}
