// CylinderCommand.cpp: implementation of the CCylinderCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "CylinderCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCylinderCommand::CCylinderCommand(CCadDoc* pDoc)
{
	m_pDoc = pDoc;
	m_pShape = new CCylinder;
}

CCylinderCommand::~CCylinderCommand()
{

}

BOOL CCylinderCommand::Execute()
{
	m_pDoc->AddShape(m_pShape);
	return TRUE;
}

BOOL CCylinderCommand::Unexecute()
{
	m_pDoc->RemoveShape(m_pShape);
	return TRUE;
}

void CCylinderCommand::OnLButtonDown( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonDown(nFlags, point);
}

void CCylinderCommand::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_pShape->OnLButtonUp(nFlags, point);
}

void CCylinderCommand::OnMouseMove( UINT nFlags, CPoint point )
{
	m_pShape->OnMouseMove(nFlags, point);
}