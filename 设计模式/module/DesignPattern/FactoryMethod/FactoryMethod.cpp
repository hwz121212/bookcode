// Factory.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/16
	FILENAME:	Factory.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	��������ģʽ����չ����-�޸ķ�գ�
		ע������򵥹���ģʽ������
		1���򵥹���ģʽ��ֻ��һ��������ȥ������Ӽ��˳���������ʵ����
		2����������ģʽ���ж���������ֱ��мӼ��˳��ȹ��������ø��ԵĹ���
		 ȥ��������Ե�������ʵ����
		3�����Խ�Ϲ���������ʹ�á�
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

// �������
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

// �ӷ�������
class OperationAdd : public Operation
{
public:
	double getResult()
	{
		return _memberA + _memberB;
	}
};

// ����������
class OperationSub : public Operation
{
	double getResult()
	{
		return _memberA - _memberB;
	}
};

// �˷�������
class OperationMul : public Operation
{
	double getResult()
	{
		return _memberA * _memberB;
	}
};

// ����������
class OperationDiv : public Operation
{
	double getResult()
	{
		double result = 0.0;
		if (_memberB == 0)
		{
			throw new exception("��������Ϊ0");
		}
		result = _memberA / _memberB;
		return result;
	}
};

// ���������
class IFactory
{
public:
	virtual Operation* createOperate() = 0;
	virtual int getID() = 0;
};

// �ӷ�����
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

// ��������
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

// �˷�����
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

// ��������
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

// ����������
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

// ע�����й���
void FactoryManager::_registerFactory()
{
	// �ӷ�����
	IFactory *pOperFactory = new AddFactory();
	addFactory(pOperFactory);
	// ��������
	pOperFactory = new SubFactory();
	addFactory(pOperFactory);
	// �˷�����
	pOperFactory = new MulFactory();
	addFactory(pOperFactory);
	// ��������
	pOperFactory = new DivFactory();
	addFactory(pOperFactory);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// �ӷ�����
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

	// ��������ĳ�ַ�����ʹ�øüӷ�����ֻ��newһ�Σ��ٷ�װһ��
	// �����д��FacrotyManager���������еĹ�����������Ҫ���Ӹ�ID
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

