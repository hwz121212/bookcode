// DihedralCommand.h: interface for the CDihedralCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIHEDRALCOMMAND_H__1D1169F4_5329_401B_A830_5999FFABE6A6__INCLUDED_)
#define AFX_DIHEDRALCOMMAND_H__1D1169F4_5329_401B_A830_5999FFABE6A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"

class CDihedralCommand : public CICommand  
{
public:
	CDihedralCommand();
	virtual ~CDihedralCommand();

};

#endif // !defined(AFX_DIHEDRALCOMMAND_H__1D1169F4_5329_401B_A830_5999FFABE6A6__INCLUDED_)
