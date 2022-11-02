// CommSocketList.cpp: implementation of the CCommSocketList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ntChatRoomServer.h"
#include "CommSocketList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommSocketList::CCommSocketList()
{
	Head=0;
}

CCommSocketList::~CCommSocketList()
{

}
BOOL CCommSocketList::Add(CCommSocket *add)
{
	CCommSocket *tmp=Head;
	if (!Head)
	{
		Head=add;
		return true;
	}
	while (tmp->Next) tmp=tmp->Next;
	tmp->Next=add;
	return true;
}

BOOL CCommSocketList::Sends(CCommSocket *tmp)
{
	char buff[1000];
	int n;
	CCommSocket *curr=Head;
	n=tmp->Receive(buff,1000);
	buff[n]=0;
	while (curr)
	{
		curr->Send(buff,n);
		curr=curr->Next;
	}
	return true;
}
