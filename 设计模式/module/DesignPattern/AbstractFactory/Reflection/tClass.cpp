
#include "stdafx.h"
#include "tClass.h"
#include "tNode.h"

tNode*	tClass::CreateObject(LPCTSTR szName)	//!< ��������һ��ʵ���ĺ���
{
	if(pfnCreateObject == NULL) return NULL;
	tNode *pObject = (*pfnCreateObject)();
	pObject->m_strName = szName;
	return pObject;
}
