// RyotaiCommand.cpp: implementation of the CRyotaiCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "RyotaiCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRyotaiCommand::CRyotaiCommand(CCadDoc* pDoc)
{
	m_pDoc = pDoc;
	m_pShape = new CRyotai;
}

CRyotaiCommand::~CRyotaiCommand()
{

}
BOOL CRyotaiCommand::Execute()
{
	m_pDoc->AddShape(m_pShape);
	return TRUE;
}

BOOL CRyotaiCommand::Unexecute()
{
	m_pDoc->RemoveShape(m_pShape);
	return TRUE;
}

void CRyotaiCommand::OnLButtonDown( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonDown(nFlags, point);
}

void CRyotaiCommand::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonUp(nFlags, point);
}

void CRyotaiCommand::OnMouseMove( UINT nFlags, CPoint point )
{
	m_pShape->OnMouseMove(nFlags, point);
}