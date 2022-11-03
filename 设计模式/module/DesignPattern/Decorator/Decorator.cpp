// Decorator.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	Decorator.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	װ��ģʽ
		��̬�ظ�һ����������һЩ�����ְ�𣨱��������������
		�����·���Ь�ӡ�����ȶ��������Ϊ���˵�װ�Ρ�

		���ֻ��һ��ConcreteComponent���û�г����Component�࣬��ôDecorator������ConcreteComponent��һ�����ࣻ
		ͬ�����ֻ��һ��ConcreteDecorator�࣬��ô���԰�Decorator��ConcreteDecorator�ϲ���һ���ࡣ

*********************************************************************/


#include "stdafx.h"
#include <iostream>


///**
//	Component�Ƕ���һ������ӿڣ����Ը���Щ����̬����ְ��
//*/
//class Component
//{
//public:
//	virtual void Operation() = 0;
//};
//
//
///**
//	ConcreteComponent�Ƕ�����һ������Ķ���Ҳ���Ը�����������ְ��
//*/
//class ConcreteComponent : public Component
//{
//public:
//	void Operation()
//	{
//		std::cout<<"�������Ĳ���"<<std::endl;
//	}
//};
//
//
///**
//	Decorator��װ�γ����࣬�̳���Component������������չComponent�Ĺ��ܡ�
//	װ��ģʽ������SetComponent���Զ�����а�װ�ġ�
//*/
//class Decorator : public Component
//{
//public:
//	void SetComponent(Component *pComponent)
//	{
//		m_pComponent = pComponent;
//	}
//
//	void Operation()
//	{
//		if (m_pComponent != NULL)
//		{
//			m_pComponent->Operation();
//		}
//	}
//
//protected:
//	Component *m_pComponent;
//};
//
//
///**
//	����װ����1
//*/
//class ConcreteDecorator1 : public Decorator
//{
//public:
//	void Operation()
//	{
//		Decorator::Operation();
//		addedState = "New State";
//		std::cout<<"����װ�ζ���1�Ĳ���"<<std::endl;
//	}
//
//private:
//	std::string addedState;
//};
//
//
///**
//	����װ����2
//*/
//class ConcreteDecorator2 : public Decorator
//{
//public:
//	void Operation()
//	{
//		Decorator::Operation();
//		AddedBehavior();
//		std::cout<<"����װ�ζ���2�Ĳ���"<<std::endl;
//	}
//
//private:
//	void AddedBehavior() {}
//};
//
//
///**
//	��ں���
//*/
//int _tmain(int argc, _TCHAR* argv[])
//{
//	// ������ConcreteComponentʵ��������pCC
//	ConcreteComponent *pCC = new ConcreteComponent();
//	ConcreteDecorator1 *pCD1 = new ConcreteDecorator1();
//	ConcreteDecorator2 *pCD2 = new ConcreteDecorator2();
//	
//	// ����pCD1����װpCC
//	pCD1->SetComponent(pCC);
//	// ����pCD2����װpCD1
//	pCD2->SetComponent(pCD1);
//	// ���ִ��pCD2�Ĳ�������
//	pCD2->Operation();
//
//	system("pause");
//	return 0;
//}
//


/**
	�൱��ConcreteComponent
*/
class Person
{
public:
	Person() {}

	Person(std::string strName)
	{
		m_strName = strName;
	}

	virtual void Show()
	{
		std::cout<<"װ���"<<m_strName.c_str()<<std::endl;
	}

private:
	std::string m_strName;
};


/**
	�൱�ڳ����Decorator
*/
class Finery : public Person
{
public:
	void Decorate(Person *pComponent)
	{
		m_pComponent = pComponent;
	}

	void Show()
	{
		if (m_pComponent)
		{
			m_pComponent->Show();
		}
	}

protected:
	Person *m_pComponent;
};


/**
	�൱�ھ����Decorator
*/
class TShirts : public Finery
{
public:
	void Show()
	{
		std::cout<<"��TѪ��"<<std::endl;
		Finery::Show();
	}
};

class BigTrousers : public Finery
{
public:
	void Show()
	{
		std::cout<<"���"<<std::endl;
		Finery::Show();
	}
};

class Sneakers : public Finery
{
public:
	void Show()
	{
		std::cout<<"����Ь"<<std::endl;
		Finery::Show();
	}
};

class Suit : public Finery
{
public:
	void Show()
	{
		std::cout<<"��װ"<<std::endl;
		Finery::Show();
	}
};

class Tie : public Finery
{
public:
	void Show()
	{
		std::cout<<"���"<<std::endl;
		Finery::Show();
	}
};

class LeatherShoes : public Finery
{
public:
	void Show()
	{
		std::cout<<"ƤЬ"<<std::endl;
		Finery::Show();
	}
};


/**
	��ں���
*/
int _tmain(int argc, _TCHAR* argv[])
{
	Person *p = new Person("С��");

	std::cout<<"��һ��װ��:"<<std::endl;
	Sneakers *sn = new Sneakers();
	BigTrousers *bi = new BigTrousers();
	TShirts *ts = new TShirts();
	sn->Decorate(p);
	bi->Decorate(sn);
	ts->Decorate(bi);
	ts->Show();

	std::cout<<"�ڶ���װ��:"<<std::endl;
	LeatherShoes *le = new LeatherShoes();
	Tie *ti = new Tie();
	Suit *su = new Suit();
	le->Decorate(p);
	ti->Decorate(le);
	su->Decorate(ti);
	su->Show();

	system("pause");
	return 0;
}
