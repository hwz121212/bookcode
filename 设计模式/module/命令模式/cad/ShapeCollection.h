// ShapeCollection.h: interface for the CShapeCollection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPECOLLECTION_H__FC90F8DA_E3C6_464D_B4F3_E82C9DCA1084__INCLUDED_)
#define AFX_SHAPECOLLECTION_H__FC90F8DA_E3C6_464D_B4F3_E82C9DCA1084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Shape.h"

class CShapeCollection  
{
	
public:
	CObList m_list;
	void Add(CShape* item);
	void Remove(CShape* item);
	CShapeCollection();
	virtual ~CShapeCollection();

};

#endif // !defined(AFX_SHAPECOLLECTION_H__FC90F8DA_E3C6_464D_B4F3_E82C9DCA1084__INCLUDED_)
