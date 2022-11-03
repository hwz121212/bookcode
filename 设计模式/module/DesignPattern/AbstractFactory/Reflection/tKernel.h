
/********************************************************************
	CREATED:	2012/01/17
	FILENAME:	tKernel.h
	AUTHOR:		By Robot
	
	PURPOSE:	数据核心
*********************************************************************/

#pragma once

#include "BasicType.h"
#include "tNode.h"

class tKernel
{
	//--------------------------------------------------
	//		定义类相关
	//--------------------------------------------------
public:
	//将某个类注册到全局类检索表函数
	VOID		ReisgerClass(tClass* pNewClass);
	//检查两个类是否具有继承关系
	BOOL		IsKindOf(const tClass* pThisClass, const tClass* pBaseClass) const;
	//根据字符串形式类名取得某定义类
	tClass*		OpenClass(LPCTSTR szClassName);

protected:
	//全局定义类检索表
	std::map< STRING, tClass* >	m_ClassMap;
	//类检索表中第一个类
	tClass*						m_pFirstClass;
	//根节点
	tNode						m_theRoot;

	//--------------------------------------------------
	//		节点管理相关
	//--------------------------------------------------
public:
	/**
		新创建一个节点加入到节点树上，所有节点的创建都应该通过这两个函数来创建
			@param
				szClassName 所创建的节点类名，该类必须已经注册过
				szPosition  所创建的节点所在的父节点的路径
				pParentNode	所创建的节点所在的父节点的指针
				szNodeName	所创建的节点的名称

		成功返回新创建的节点，如果失败,返回NULL	
	*/
	///根据字符串形式路径来创建
	virtual tNode*	NewNode(LPCTSTR szClassName, LPCTSTR szPosition, LPCTSTR szNodeName);
	///根据父节点指针形式来创建
	virtual tNode*	NewNode(LPCTSTR szClassName, tNode* pParentNode, LPCTSTR szNodeName);

	///根据路径名取得节点，例如 pNode = GetNode("scene\\object")
	virtual tNode*	GetNode(LPCTSTR szPathName);

public:
	tKernel(VOID);
	virtual ~tKernel(VOID);
	//得到自身
	static tKernel* GetMe(VOID) { return s_pMe; }

protected:
	static tKernel*		s_pMe;
};

