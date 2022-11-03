// HexagonalCommand.cpp: implementation of the CHexagonalCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "HexagonalCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHexagonalCommand::CHexagonalCommand(CCadDoc* pDoc)
{
	m_pDoc = pDoc;
	m_pShape = new CHexagonal;
}	

CHexagonalCommand::~CHexagonalCommand()
{

}
BOOL CHexagonalCommand::Execute()
{
	m_pDoc->AddShape(m_pShape);
	return TRUE;
}

BOOL CHexagonalCommand::Unexecute()
{
	m_pDoc->RemoveShape(m_pShape);
	return TRUE;
}

void CHexagonalCommand::OnLButtonDown( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonDown(nFlags, point);
}

void CHexagonalCommand::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonUp(nFlags, point);
}

void CHexagonalCommand::OnMouseMove( UINT nFlags, CPoint point )
{
	m_pShape->OnMouseMove(nFlags, point);
}
