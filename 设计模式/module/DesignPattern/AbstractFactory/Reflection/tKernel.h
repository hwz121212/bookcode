
/********************************************************************
	CREATED:	2012/01/17
	FILENAME:	tKernel.h
	AUTHOR:		By Robot
	
	PURPOSE:	���ݺ���
*********************************************************************/

#pragma once

#include "BasicType.h"
#include "tNode.h"

class tKernel
{
	//--------------------------------------------------
	//		���������
	//--------------------------------------------------
public:
	//��ĳ����ע�ᵽȫ�����������
	VOID		ReisgerClass(tClass* pNewClass);
	//����������Ƿ���м̳й�ϵ
	BOOL		IsKindOf(const tClass* pThisClass, const tClass* pBaseClass) const;
	//�����ַ�����ʽ����ȡ��ĳ������
	tClass*		OpenClass(LPCTSTR szClassName);

protected:
	//ȫ�ֶ����������
	std::map< STRING, tClass* >	m_ClassMap;
	//��������е�һ����
	tClass*						m_pFirstClass;
	//���ڵ�
	tNode						m_theRoot;

	//--------------------------------------------------
	//		�ڵ�������
	//--------------------------------------------------
public:
	/**
		�´���һ���ڵ���뵽�ڵ����ϣ����нڵ�Ĵ�����Ӧ��ͨ������������������
			@param
				szClassName �������Ľڵ���������������Ѿ�ע���
				szPosition  �������Ľڵ����ڵĸ��ڵ��·��
				pParentNode	�������Ľڵ����ڵĸ��ڵ��ָ��
				szNodeName	�������Ľڵ������

		�ɹ������´����Ľڵ㣬���ʧ��,����NULL	
	*/
	///�����ַ�����ʽ·��������
	virtual tNode*	NewNode(LPCTSTR szClassName, LPCTSTR szPosition, LPCTSTR szNodeName);
	///���ݸ��ڵ�ָ����ʽ������
	virtual tNode*	NewNode(LPCTSTR szClassName, tNode* pParentNode, LPCTSTR szNodeName);

	///����·����ȡ�ýڵ㣬���� pNode = GetNode("scene\\object")
	virtual tNode*	GetNode(LPCTSTR szPathName);

public:
	tKernel(VOID);
	virtual ~tKernel(VOID);
	//�õ�����
	static tKernel* GetMe(VOID) { return s_pMe; }

protected:
	static tKernel*		s_pMe;
};

