// Strategy.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/30
	FILENAME:	Strategy.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	����ģʽ
		�������㷨���壬�ֱ��װ������������֮����Ի����滻��
		��ģʽ���㷨�ı仯������Ӱ�쵽ʹ���㷨�Ŀͻ���
		����ģʽ��򵥹����Ľ��ʹ�ã�
			ʹ�ü򵥹���ģʽģʽ��Ҫ�ÿͻ���֪�������ࣺCashSuperStrategy �� CashSuperStrategyFactory
			������ģʽ��򵥹���ģʽ��Ϻ󣬿ͻ���ֻ��Ҫ֪��һ����CashContext�Ϳ�������

		�ܽ᣺����ģʽ��һ�ֶ���һϵ���㷨�ķ�����������Щ�㷨��ɵĶ�����ͬ�Ĺ�����ֻ��ʵ�ֲ�ͬ��
		����������ͬ�ķ�ʽ�������е��㷨�������˸����㷨����ʹ���㷨��֮�����ϣ�
		�ڻ����Ĳ���ģʽ�У�ѡ�����þ���ʵ�ֵ�ְ���ɿͻ��˶���е�����ת������ģʽ��Context����
		������ģʽ��򵥹�������Ժ�ѡ�����ʵ�ֵ�ְ��Ҳ������Context�е���

*********************************************************************/


#include "stdafx.h"
#include <iostream>

/**
	���Ͷ���
*/
#ifdef UNICODE
typedef	std::wstring	STRING;
#else
typedef	std::string		STRING;
#endif


/**
	���������
*/
class CashSuperStrategy
{
public:
	virtual double acceptCash(double money) = 0;
};


/**
	�����շ���
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
	�ۿ��շ���
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
	�����շ���
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
	������򵥹������
*/
class CashContext
{
public:
	CashContext(STRING type)
	{
		if (type.compare(_T("�����շ�")) == 0)
		{
			CashNormalStrategy *pCS = new CashNormalStrategy();
			m_pCSStrategy = pCS;
		}
		else if (type.compare(_T("��300��100")) == 0)
		{
			CashReturnStrategy *pCS = new CashReturnStrategy(300,100);
			m_pCSStrategy = pCS;
		}
		else if (type.compare(_T("��8��")) == 0)
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
	��ں���
*/
int _tmain(int argc, _TCHAR* argv[])
{
	CashContext *pCSSuper = new CashContext(_T("��300��100"));
	double totalPrices = 0.0;
	totalPrices = pCSSuper->GetResult(50*20);
	
	system("pause");
	return 0;
}

