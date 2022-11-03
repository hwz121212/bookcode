// Dihedral.h: interface for the CDihedral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIHEDRAL_H__ABC90FEA_3912_4C41_AC73_29D889ED8497__INCLUDED_)
#define AFX_DIHEDRAL_H__ABC90FEA_3912_4C41_AC73_29D889ED8497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CDihedral : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CDihedral();
	virtual ~CDihedral();

};

#endif // !defined(AFX_DIHEDRAL_H__ABC90FEA_3912_4C41_AC73_29D889ED8497__INCLUDED_)
