// Ytt.h: interface for the CYtt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YTT_H__657810FA_71E9_4060_A11E_4CD260772D49__INCLUDED_)
#define AFX_YTT_H__657810FA_71E9_4060_A11E_4CD260772D49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CYtt : public CShape  
{
	Point m_ptStart;
	Point m_ptEnd;
public:
	CYtt();
	virtual ~CYtt();

};

#endif // !defined(AFX_YTT_H__657810FA_71E9_4060_A11E_4CD260772D49__INCLUDED_)
