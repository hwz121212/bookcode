// Factory.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/16
	FILENAME:	Factory.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	工厂方法模式（扩展开放-修改封闭）
		注意它与简单工厂模式的区别：
		1、简单工厂模式中只有一个工厂，去构造出加减乘除等运算类实例；
		2、工厂方法模式中有多个工厂，分别有加减乘除等工厂，再用各自的工厂
		 去构造出各自的运算类实例；
		3、可以结合工厂管理器使用。
*********************************************************************/

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

enum
{
	OPER_INVALID = -1,
	OPER_ADD,
	OPER_SUB,
	OPER_MUL,
	OPER_DIV,
	OPER_NUM,
};

// 运算基类
class Operation
{
public:
	virtual double getResult() { return 0; }
public:
	void	setA(double val) { _memberA = val; }
	double	getA() { return _memberA; }
	void	setB(double val) { _memberB = val; }
	double	getB() { return _memberB; }

protected:
	double _memberA;
	double _memberB;
};

// 加法运算类
class OperationAdd : public Operation
{
public:
	double getResult()
	{
		return _memberA + _memberB;
	}
};

// 减法运算类
class OperationSub : public Operation
{
	double getResult()
	{
		return _memberA - _memberB;
	}
};

// 乘法运算类
class OperationMul : public Operation
{
	double getResult()
	{
		return _memberA * _memberB;
	}
};

// 除法运算类
class OperationDiv : public Operation
{
	double getResult()
	{
		double result = 0.0;
		if (_memberB == 0)
		{
			throw new exception("除数不能为0");
		}
		result = _memberA / _memberB;
		return result;
	}
};

// 工厂虚基类
class IFactory
{
public:
	virtual Operation* createOperate() = 0;
	virtual int getID() = 0;
};

// 加法工厂
class AddFactory : public IFactory
{
public:
	Operation* createOperate()
	{
		return new OperationAdd();
	}
	int getID()
	{
		return OPER_ADD;
	}
};

// 减法工厂
class SubFactory : public IFactory
{
public:
	Operation* createOperate()
	{
		return new OperationSub();
	}
	int getID()
	{
		return OPER_SUB;
	}
};

// 乘法工厂
class MulFactory : public IFactory
{
public:
	Operation* createOperate()
	{
		return  new OperationMul();
	}
	int getID()
	{
		return OPER_MUL;
	}
};

// 除法工厂
class DivFactory : public IFactory
{
	Operation* createOperate()
	{
		return new OperationDiv();
	}
	int getID()
	{
		return OPER_DIV;
	}
};

// 工厂管理器
class FactoryManager
{
public:
	FactoryManager();
	~FactoryManager();
	void addFactory(IFactory* pFactory);
	Operation* createOperate(int id);

private:
	void _registerFactory();

private:
	IFactory** pFactoryArry;
};

FactoryManager::FactoryManager()
{
	pFactoryArry = new IFactory*[OPER_NUM];
	for (int i = 0; i < OPER_NUM; i++)
	{
		pFactoryArry[i] = NULL;
	}
	_registerFactory();
}

FactoryManager::~FactoryManager()
{
	delete []pFactoryArry;
	pFactoryArry = NULL;
}

void FactoryManager::addFactory(IFactory* pFactory)
{
	if (NULL == pFactory || NULL != pFactoryArry[pFactory->getID()])
	{
		return;
	}
	pFactoryArry[pFactory->getID()] = pFactory;
}

Operation* FactoryManager::createOperate(int id)
{
	if (id <= OPER_INVALID || id >= OPER_NUM)
	{
		return NULL;
	}
	IFactory *pFactory = pFactoryArry[id];
	if (NULL == pFactory)
	{
		return NULL;
	}
	return pFactory->createOperate();
}

// 注册所有工厂
void FactoryManager::_registerFactory()
{
	// 加法工厂
	IFactory *pOperFactory = new AddFactory();
	addFactory(pOperFactory);
	// 减法工厂
	pOperFactory = new SubFactory();
	addFactory(pOperFactory);
	// 乘法工厂
	pOperFactory = new MulFactory();
	addFactory(pOperFactory);
	// 除法工厂
	pOperFactory = new DivFactory();
	addFactory(pOperFactory);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// 加法运算
	//IFactory *pOperFactory = new AddFactory();
	//double result = 0.0;

	//if (NULL != pOperFactory)
	//{
	//	Operation *pOperObj = pOperFactory->createOperate();
	//	if (NULL != pOperObj)
	//	{
	//		pOperObj->setA(1.0);
	//		pOperObj->setB(2.0);
	//		result = pOperObj->getResult();
	//	}
	//}

	// 可以利用某种方法，使得该加法工厂只被new一次，再封装一层
	// 例如可写个FacrotyManager，管理所有的工厂，这里需要增加个ID
	FactoryManager factoryMgn;
	double result = 0.0;
	Operation* pOperObj = factoryMgn.createOperate(OPER_ADD);
	if (NULL != pOperObj)
	{
		pOperObj->setA(1.0);
		pOperObj->setB(2.0);
		result = pOperObj->getResult();
	}

	system("pause");
	return 0;
}

