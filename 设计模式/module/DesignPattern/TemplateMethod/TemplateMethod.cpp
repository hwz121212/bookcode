// TemplateMethod.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/31
	FILENAME:	TemplateMethod.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	模板方法模式
		定义一个操作中的算法骨架，而将一些步骤延迟到子类中。使得子类可以不改变一个
		算法的结构，即可重定义该算法的某些特定步骤。

*********************************************************************/

#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

/**
	抽象类，其实也是一个抽象模板，定义并实现了一个模板的方法。
	这个模板方法一般是一个具体方法，他给出了一个顶级逻辑的骨架，
	而逻辑的组成步骤在相应的抽象操作中，推迟到子类中实现。
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
	每一个ConcreteClass都可以给出这些抽象方法的不同实现，
	从而使得顶级逻辑的实现各不相同。
*/
class ConcreteClass1 : public AbstractClass
{
private:
	virtual void PrimitiveOperation1()
	{
		cout<<"具体类1方法1的实现"<<endl;
	}

	virtual void PrimitiveOperation2()
	{
		cout<<"具体类1方法2的实现"<<endl;
	}
};

class ConcreteClass2 : public AbstractClass
{
private:
	virtual void PrimitiveOperation1()
	{
		cout<<"具体类2方法1的实现"<<endl;
	}

	virtual void PrimitiveOperation2()
	{
		cout<<"具体类2方法2的实现"<<endl;
	}
};


/**
	入口函数
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

