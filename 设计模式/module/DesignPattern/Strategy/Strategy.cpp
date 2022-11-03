// Strategy.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/30
	FILENAME:	Strategy.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	策略模式
		定义了算法家族，分别封装起来，让他们之间可以互相替换；
		此模式让算法的变化，不会影响到使用算法的客户。
		策略模式与简单工厂的结合使用：
			使用简单工厂模式模式需要让客户端知道两个类：CashSuperStrategy 与 CashSuperStrategyFactory
			而策略模式与简单工厂模式结合后，客户端只需要知道一个类CashContext就可以啦。

		总结：策略模式是一种定义一系列算法的方法，所有这些算法完成的都是相同的工作，只是实现不同。
		它可以以相同的方式调用所有的算法，减少了各种算法类与使用算法类之间的耦合；
		在基本的策略模式中，选择所用具体实现的职责由客户端对象承担，并转给策略模式的Context对象。
		而策略模式与简单工厂结合以后，选择具体实现的职责也可以由Context承担。

*********************************************************************/


#include "stdafx.h"
#include <iostream>

/**
	类型定义
*/
#ifdef UNICODE
typedef	std::wstring	STRING;
#else
typedef	std::string		STRING;
#endif


/**
	策略虚基类
*/
class CashSuperStrategy
{
public:
	virtual double acceptCash(double money) = 0;
};


/**
	正常收费类
*/
class CashNormalStrategy : public CashSuperStrategy
{
public:
	double acceptCash(double money)
	{
		return money;
	}
};


/**
	折扣收费类
*/
class CashRebateStrategy : public CashSuperStrategy
{
public:
	CashRebateStrategy(double moneyRebate)
	{
		m_moneyRebate = moneyRebate;
	}

	double acceptCash(double money)
	{
		return money*m_moneyRebate;
	}

private:
	double m_moneyRebate;
};


/**
	返利收费类
*/
class CashReturnStrategy : public CashSuperStrategy
{
public:
	CashReturnStrategy(double moneyCondition, double moneyReturn)
	{
		m_moneyCondition = moneyCondition;
		m_moneyReturn = moneyReturn;
	}

	double acceptCash(double money)
	{
		double result = money;
		if (money >= m_moneyCondition)
			result = money - ((int)money/(int)m_moneyCondition)*m_moneyReturn;
		return result;
	}

private:
	double m_moneyCondition;
	double m_moneyReturn;
};


/**
	策略与简单工厂结合
*/
class CashContext
{
public:
	CashContext(STRING type)
	{
		if (type.compare(_T("正常收费")) == 0)
		{
			CashNormalStrategy *pCS = new CashNormalStrategy();
			m_pCSStrategy = pCS;
		}
		else if (type.compare(_T("满300返100")) == 0)
		{
			CashReturnStrategy *pCS = new CashReturnStrategy(300,100);
			m_pCSStrategy = pCS;
		}
		else if (type.compare(_T("打8折")) == 0)
		{
			CashRebateStrategy *pCS = new CashRebateStrategy(0.8);
			m_pCSStrategy = pCS;
		}
	}

	double GetResult(double money)
	{
		if (m_pCSStrategy != NULL)
		{
			return m_pCSStrategy->acceptCash(money);
		}
		else
		{
			return 0.0;
		}
	}

private:
	CashSuperStrategy *m_pCSStrategy;
};


/**
	入口函数
*/
int _tmain(int argc, _TCHAR* argv[])
{
	CashContext *pCSSuper = new CashContext(_T("满300返100"));
	double totalPrices = 0.0;
	totalPrices = pCSSuper->GetResult(50*20);
	
	system("pause");
	return 0;
}

