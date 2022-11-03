// Factory.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/16
	FILENAME:	Factory.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	�򵥹���ģʽ
		1. ʹ�����װ
		2. ����չ��ʹ�ü̳����̬��
		3. ʹ��һ������������������ʵ���Ĺ��̣�����ǹ�����	
*********************************************************************/

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

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

// �����๤��
class OperationFactory
{
public:
	static Operation* createOperate(char oper)
	{
		Operation *pOperObj = NULL;
		switch(oper)
		{
		case '+':
			{
				pOperObj = new OperationAdd();
			}
			break;
		case '-':
			{
				pOperObj = new OperationSub();
			}
			break;
		case '*':
			{
				pOperObj = new OperationMul();
			}
			break;
		case '/':
			{
				pOperObj = new OperationDiv();
			}
			break;
		default:
			return NULL;
		}
		return pOperObj;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	// �ӷ�����
	Operation *pOperAdd = OperationFactory::createOperate('+');
	double result = 0.0;
	if (NULL != pOperAdd)
	{
		pOperAdd->setA(1.0);
		pOperAdd->setB(2.0);
		result = pOperAdd->getResult();
	}

	system("pause");
	return 0;
}

