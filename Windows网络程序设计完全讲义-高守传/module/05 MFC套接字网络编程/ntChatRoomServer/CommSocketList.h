// CommSocketList.h: interface for the CCommSocketList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMSOCKETLIST_H__2093D705_D3E8_4C16_974E_1A1401A38F5B__INCLUDED_)
#define AFX_COMMSOCKETLIST_H__2093D705_D3E8_4C16_974E_1A1401A38F5B__INCLUDED_
#include "CommSocket.h"//CCommSocket���ͷ�ļ�
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommSocketList  
{
public:
	CCommSocketList();
	virtual ~CCommSocketList();
	BOOL Sends(CCommSocket *);//��������
	BOOL Add(CCommSocket *);//�������
	CCommSocket * Head;//����ͷ
};

#endif // !defined(AFX_COMMSOCKETLIST_H__2093D705_D3E8_4C16_974E_1A1401A38F5B__INCLUDED_)
