// TriangleCommand.cpp: implementation of the CTriangleCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "TriangleCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTriangleCommand::CTriangleCommand(CCadDoc* pDoc)
{
	m_pDoc = pDoc;
	m_pShape = new CTriangle;
}

CTriangleCommand::~CTriangleCommand()
{

}

BOOL CTriangleCommand::Execute()
{
	m_pDoc->AddShape(m_pShape);
	return TRUE;
}

BOOL CTriangleCommand::Unexecute()
{
	m_pDoc->RemoveShape(m_pShape);
	return TRUE;
}

void CTriangleCommand::OnLButtonDown( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonDown(nFlags, point);
}

void CTriangleCommand::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonUp(nFlags, point);
}

void CTriangleCommand::OnMouseMove( UINT nFlags, CPoint point )
{
	m_pShape->OnMouseMove(nFlags, point);
}
