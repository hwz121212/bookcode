// ShapeCollection.cpp: implementation of the CShapeCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "ShapeCollection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeCollection::CShapeCollection()
{

}

CShapeCollection::~CShapeCollection()
{

}

void CShapeCollection::Add( CShape* item )
{
	m_list.AddTail(item);
}

void CShapeCollection::Remove(CShape* item)
{
	POSITION ps = m_list.Find(item);
	if (ps != NULL)
	{
		m_list.RemoveAt(ps);
	}
}
