
#include "stdafx.h"
#include "tUtil.h"
#include "tKernel.h"

tKernel* tKernel::s_pMe = NULL;
tKernel::tKernel(VOID)
: m_theRoot(_T("root"))
, m_pFirstClass(NULL)
{
	s_pMe = this;
}

tKernel::~tKernel(VOID)
{
}

//��ĳ����ע�ᵽȫ�����������
VOID tKernel::ReisgerClass(tClass* pNewClass)
{
	assert(pNewClass);

	if(m_ClassMap[STRING(pNewClass->szClassName)] != NULL)
	{
		throw(_T("Multi register class:%s"), pNewClass->szClassName);
	}
	pNewClass->pNextClass = m_pFirstClass;
	m_pFirstClass = pNewClass;
	//���µ�����뵽�������
	(m_ClassMap)[pNewClass->szClassName] = pNewClass;
}

//����������Ƿ���м̳й�ϵ
BOOL tKernel::IsKindOf(const tClass* pThisClass, const tClass* pBaseClass) const
{
	if(!pBaseClass || !pThisClass) return FALSE;

	register const tClass *pClass = pThisClass;

	while(pClass != NULL)
	{
		if(pClass == pBaseClass)
		{
			return TRUE;
		}
		pClass = pClass->pBaseClass;
	}
	return FALSE;
}
//�����ַ�����ʽ����ȡ��ĳ������
tClass* tKernel::OpenClass(LPCTSTR szClassName)
{
	std::map< STRING, tClass* >::iterator it = m_ClassMap.find(szClassName);
	if(it == m_ClassMap.end()) return 0;
	else return it->second;
}

//�����ַ�����ʽ��·���������½ڵ�
tNode*	tKernel::NewNode(LPCTSTR szClassName, LPCTSTR szPosition, LPCTSTR szNodeName)
{
	assert(szClassName && szPosition && szNodeName);

	//����
	tClass *pClass = OpenClass(szClassName);
	if(!pClass)
	{
		throw(_T("(tKernel::NewNode)Can't create new Node[%s]"), szClassName);
	}

	std::vector< STRING > vPathSplitBuf;
	ConvertStringToVector(szPosition, vPathSplitBuf, _T("\\/"));

	tNode *pCurrentNode = &m_theRoot;
	tNode *pFindNode = NULL;

	//�������ڵ�
	for(register INT i=0; i<(INT)vPathSplitBuf.size(); i++)
	{
		tNode *pFindNode = pCurrentNode->LookUpChild((LPCTSTR)vPathSplitBuf[i].c_str());
		if(pFindNode == NULL)
		{
			tNode *pNewNode = new tNode(vPathSplitBuf[i].c_str());
			pCurrentNode->AddChild(pNewNode);
			pFindNode = pNewNode;
		}
		pCurrentNode = pFindNode;
	}

	//�����Ƿ�ýڵ��Ѿ�����
	if(pCurrentNode->LookUpChild(szNodeName))
	{
		throw(_T("(tKernel::NewNode)The Node[%s] has exist!"), szNodeName);
	}

	tNode *pNewNode = (tNode *)pClass->CreateObject(szNodeName);
	pCurrentNode->AddChild(pNewNode);
	return pNewNode;
}

//���ݸ��ڵ�����µĽڵ�
tNode*	tKernel::NewNode(LPCTSTR szClassName, tNode* pParentNode, LPCTSTR szNodeName)
{
	assert(szClassName && pParentNode && szNodeName);

	//����
	tClass *pClass = OpenClass(szClassName);
	if(!pClass)
	{
		throw(_T("(tKernel::NewNode)Can't create new Node[%s]"), szClassName);
	}

	//�����Ƿ�ýڵ��Ѿ�����
	if(pParentNode->LookUpChild(szNodeName))
	{
		throw(_T("(tKernel::NewNode)The Node[%s] has exist!"), szNodeName);
	}

	tNode *pNewNode = (tNode *)pClass->CreateObject(szNodeName);
	pParentNode->AddChild(pNewNode);

	return pNewNode;
}


tNode*	tKernel::GetNode(LPCTSTR szPathName)
{
	assert(szPathName);

	std::vector< STRING > vPathSplitBuf;
	ConvertStringToVector(szPathName, vPathSplitBuf, _T("\\/"));

	if(vPathSplitBuf.empty()) return NULL;

	tNode *pCurrentNode = &m_theRoot;
	for(register INT i=0; i<(INT)vPathSplitBuf.size(); i++)
	{
		tNode *pFindNode = pCurrentNode->LookUpChild((LPCTSTR)vPathSplitBuf[i].c_str());
		if(pFindNode == NULL)
		{
			return NULL;
		}
		pCurrentNode = pFindNode;
	}

	return pCurrentNode;
}

