// Factory.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/16
	FILENAME:	Factory.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	简单工厂模式
		1. 使用类封装
		2. 易扩展（使用继承与多态）
		3. 使用一个单独的类来做创造实例的过程（这就是工厂）	
*********************************************************************/

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

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

// 运算类工厂
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
	// 加法运算
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

