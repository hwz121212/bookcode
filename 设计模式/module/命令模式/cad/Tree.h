// Tree.h: interface for the CTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREE_H__3AD3A30C_DE4F_4E6B_A918_F22D1412F5B6__INCLUDED_)
#define AFX_TREE_H__3AD3A30C_DE4F_4E6B_A918_F22D1412F5B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Page.h"

class CTree : public CObject  
{
public:
	list<CPage*> m_listPage;
	CTree();
	virtual ~CTree();

};

#endif // !defined(AFX_TREE_H__3AD3A30C_DE4F_4E6B_A918_F22D1412F5B6__INCLUDED_)
