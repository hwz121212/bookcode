// YttCommand.h: interface for the CYttCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YTTCOMMAND_H__1ABA5856_AFB9_4505_84BA_58D3BC47D13C__INCLUDED_)
#define AFX_YTTCOMMAND_H__1ABA5856_AFB9_4505_84BA_58D3BC47D13C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"

class CYttCommand : public CICommand  
{
public:
	CYttCommand();
	virtual ~CYttCommand();

};

#endif // !defined(AFX_YTTCOMMAND_H__1ABA5856_AFB9_4505_84BA_58D3BC47D13C__INCLUDED_)
