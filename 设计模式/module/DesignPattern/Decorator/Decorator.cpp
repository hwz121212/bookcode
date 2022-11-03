// Decorator.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	Decorator.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	装饰模式
		动态地给一个对象增加一些额外的职责（比生成子类更灵活）；
		无论衣服、鞋子、领带等都可以理解为对人的装饰。

		如果只有一个ConcreteComponent类而没有抽象的Component类，那么Decorator可以是ConcreteComponent的一个子类；
		同理，如果只有一个ConcreteDecorator类，那么可以把Decorator与ConcreteDecorator合并成一个类。

*********************************************************************/


#include "stdafx.h"
#include <iostream>


///**
//	Component是定义一个对象接口，可以给这些对象动态增加职责。
//*/
//class Component
//{
//public:
//	virtual void Operation() = 0;
//};
//
//
///**
//	ConcreteComponent是定义了一个具体的对象，也可以给这个对象添加职责。
//*/
//class ConcreteComponent : public Component
//{
//public:
//	void Operation()
//	{
//		std::cout<<"具体对象的操作"<<std::endl;
//	}
//};
//
//
///**
//	Decorator是装饰抽象类，继承于Component，从外类来扩展Component的功能。
//	装饰模式是利用SetComponent来对对象进行包装的。
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
//	具体装饰类1
//*/
//class ConcreteDecorator1 : public Decorator
//{
//public:
//	void Operation()
//	{
//		Decorator::Operation();
//		addedState = "New State";
//		std::cout<<"具体装饰对象1的操作"<<std::endl;
//	}
//
//private:
//	std::string addedState;
//};
//
//
///**
//	具体装饰类2
//*/
//class ConcreteDecorator2 : public Decorator
//{
//public:
//	void Operation()
//	{
//		Decorator::Operation();
//		AddedBehavior();
//		std::cout<<"具体装饰对象2的操作"<<std::endl;
//	}
//
//private:
//	void AddedBehavior() {}
//};
//
//
///**
//	入口函数
//*/
//int _tmain(int argc, _TCHAR* argv[])
//{
//	// 首先用ConcreteComponent实例化对象pCC
//	ConcreteComponent *pCC = new ConcreteComponent();
//	ConcreteDecorator1 *pCD1 = new ConcreteDecorator1();
//	ConcreteDecorator2 *pCD2 = new ConcreteDecorator2();
//	
//	// 再用pCD1来包装pCC
//	pCD1->SetComponent(pCC);
//	// 再用pCD2来包装pCD1
//	pCD2->SetComponent(pCD1);
//	// 最后执行pCD2的操作函数
//	pCD2->Operation();
//
//	system("pause");
//	return 0;
//}
//


/**
	相当于ConcreteComponent
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
		std::cout<<"装扮的"<<m_strName.c_str()<<std::endl;
	}

private:
	std::string m_strName;
};


/**
	相当于抽象的Decorator
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
	相当于具体的Decorator
*/
class TShirts : public Finery
{
public:
	void Show()
	{
		std::cout<<"大T血衫"<<std::endl;
		Finery::Show();
	}
};

class BigTrousers : public Finery
{
public:
	void Show()
	{
		std::cout<<"垮裤"<<std::endl;
		Finery::Show();
	}
};

class Sneakers : public Finery
{
public:
	void Show()
	{
		std::cout<<"破球鞋"<<std::endl;
		Finery::Show();
	}
};

class Suit : public Finery
{
public:
	void Show()
	{
		std::cout<<"西装"<<std::endl;
		Finery::Show();
	}
};

class Tie : public Finery
{
public:
	void Show()
	{
		std::cout<<"领带"<<std::endl;
		Finery::Show();
	}
};

class LeatherShoes : public Finery
{
public:
	void Show()
	{
		std::cout<<"皮鞋"<<std::endl;
		Finery::Show();
	}
};


/**
	入口函数
*/
int _tmain(int argc, _TCHAR* argv[])
{
	Person *p = new Person("小菜");

	std::cout<<"第一种装扮:"<<std::endl;
	Sneakers *sn = new Sneakers();
	BigTrousers *bi = new BigTrousers();
	TShirts *ts = new TShirts();
	sn->Decorate(p);
	bi->Decorate(sn);
	ts->Decorate(bi);
	ts->Show();

	std::cout<<"第二种装扮:"<<std::endl;
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
