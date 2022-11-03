// TemplateMethod.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	TemplateMethod.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	ģ�巽��ģʽ
		����һ�������е��㷨�Ǽܣ�����һЩ�����ӳٵ������С�ʹ��������Բ��ı�һ��
		�㷨�Ľṹ�������ض�����㷨��ĳЩ�ض����衣

*********************************************************************/

#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

/**
	�����࣬��ʵҲ��һ������ģ�壬���岢ʵ����һ��ģ��ķ�����
	���ģ�巽��һ����һ�����巽������������һ�������߼��ĹǼܣ�
	���߼�����ɲ�������Ӧ�ĳ�������У��Ƴٵ�������ʵ�֡�
*/
class AbstractClass 
{
public:
	void TemplateMethod()
	{
		PrimitiveOperation1();
		PrimitiveOperation2();
	}

private:
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
};


/**
	ÿһ��ConcreteClass�����Ը�����Щ���󷽷��Ĳ�ͬʵ�֣�
	�Ӷ�ʹ�ö����߼���ʵ�ָ�����ͬ��
*/
class ConcreteClass1 : public AbstractClass
{
private:
	virtual void PrimitiveOperation1()
	{
		cout<<"������1����1��ʵ��"<<endl;
	}

	virtual void PrimitiveOperation2()
	{
		cout<<"������1����2��ʵ��"<<endl;
	}
};

class ConcreteClass2 : public AbstractClass
{
private:
	virtual void PrimitiveOperation1()
	{
		cout<<"������2����1��ʵ��"<<endl;
	}

	virtual void PrimitiveOperation2()
	{
		cout<<"������2����2��ʵ��"<<endl;
	}
};


/**
	��ں���
*/
int _tmain(int argc, _TCHAR* argv[])
{
	AbstractClass *p;
	p = new ConcreteClass1();
	p->TemplateMethod();

	p = new ConcreteClass2();
	p->TemplateMethod();

	system("pause");
	return 0;
}

