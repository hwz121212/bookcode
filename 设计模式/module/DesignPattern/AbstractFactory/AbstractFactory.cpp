// AbstractFactory.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/17
	FILENAME:	AbstractFactory.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	抽象工厂模式
		当工厂方法模式中不止一类产品时候（如Operation是一类产品），就变成了抽象工厂模式
		例如，下面程序例子
		此时，IFactory接口中创建所有产品（User和Department）的抽象方法。
*********************************************************************/

#include "stdafx.h"
#include "Reflection/tClass.h"
#include "Reflection/tKernel.h"
#include "Reflection/BasicType.h"
#include <iostream>

using namespace std;

/**
	抽象工厂模式
*/

//// User数结构
//class User
//{
//public:
//	int GetID() { return _id; }
//	void SetID(int id) { _id = id; }
//
//	string GetName() { return _name; }
//	void SetName(string name) { _name = name; }
//
//private:
//	int _id;
//	string _name;
//};
//
//// Department表结构
//class Department
//{
//public:
//	int GetID() { return _id; }
//	void SetID(int id) { _id = id; }
//
//private:
//	int _id;
//};
//
//// 虚基类
//class IUser
//{
//public:
//	virtual void Insert(User* user) = 0;
//	virtual User* GetUser(int id) = 0;
//};
//
//class IDepartment
//{
//public:
//	virtual void Insert(Department* department) = 0;
//	virtual Department* GetDepartment(int id) = 0;
//};
//
//// SqlServer DB
//class SqlServerUser : public IUser
//{
//public:
//	void Insert(User* user)
//	{
//		cout << "在SqlServer中给User表中增加一条记录" <<endl;
//	}
//	User* GetUser(int id)
//	{
//		cout << "在SqlServer中根据ID得到User表中的一条记录" <<endl;
//		return NULL;
//	}
//};
//
//class SqlServerDepartment : public IDepartment
//{
//public:
//	void Insert(Department* department)
//	{
//		cout << "在SqlServer中给Department表中增加一条记录" <<endl;
//	}
//	Department* GetDepartment(int id)
//	{
//		cout << "在SqlServer中根据ID得到Department表中的一条记录" <<endl;
//		return NULL;
//	}
//};
//
//// Access DB
//class AccessUser : public IUser
//{
//public:
//	void Insert(User* user)
//	{
//		cout << "在Access中给User表中增加一条记录" <<endl;
//	}
//	User* GetUser(int id)
//	{
//		cout << "在Access中根据ID得到User表中的一条记录" <<endl;
//		return NULL;
//	}
//};
//
//class AccessDepartment : public IDepartment
//{
//public:
//	void Insert(Department* department)
//	{
//		cout << "在Access中给Department表中增加一条记录" <<endl;
//	}
//	Department* GetDepartment(int id)
//	{
//		cout << "在Access中根据ID得到Department表中的一条记录" <<endl;
//		return NULL;
//	}
//};
//
//// 工厂虚基类
//class IFactory
//{
//public:
//	virtual IUser* CreateUser() = 0;
//	virtual IDepartment* CreateDepartment() = 0;
//};
//
//// 
//class SqlServerFactory : public IFactory
//{
//public:
//	IUser* CreateUser()
//	{
//		return new SqlServerUser();
//	}
//	IDepartment* CreateDepartment()
//	{
//		return new SqlServerDepartment();
//	}
//};
//
////
//class AccessFactory : public IFactory
//{
//public:
//	IUser* CreateUser()
//	{
//		return new AccessUser();
//	}
//	IDepartment* CreateDepartment()
//	{
//		return new AccessDepartment();
//	}
//};
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	User user;
//	Department dept;
//
//	IFactory *pFactory = new AccessFactory(); //new SqlServerFactory();
//
//	IUser *pUser = pFactory->CreateUser();
//	pUser->Insert(&user);
//	pUser->GetUser(0);
//
//	IDepartment* pDept = pFactory->CreateDepartment();
//	pDept->Insert(&dept);
//	pDept->GetDepartment(0);
//
//	system("pause");
//	return 0;
//}


/**
	使用反射机制&简单工厂模式来改进抽象工厂模式
*/

tKernel g_theKernel;

// User数结构
class User
{
public:
	int GetID() { return _id; }
	void SetID(int id) { _id = id; }

	string GetName() { return _name; }
	void SetName(string name) { _name = name; }

private:
	int _id;
	string _name;
};

// Department表结构
class Department
{
public:
	int GetID() { return _id; }
	void SetID(int id) { _id = id; }

private:
	int _id;
};

// 虚基类（利用tNode实现C++反射）
class IUser : public tNode
{
public:
	virtual void Insert(User* user) = 0;
	virtual User* GetUser(int id) = 0;
	WX_DECLARE_DYNAMIC(IUser);
};
WX_IMPLEMENT_DYNAMIC_VIRTUAL(IUser, GETCLASS(tNode));

class IDepartment : public tNode
{
public:
	virtual void Insert(Department* department) = 0;
	virtual Department* GetDepartment(int id) = 0;
	WX_DECLARE_DYNAMIC(IDepartment);
};
WX_IMPLEMENT_DYNAMIC_VIRTUAL(IDepartment, GETCLASS(tNode));

// SqlServer DB
class SqlServerUser : public IUser
{
public:
	void Insert(User* user)
	{
		cout << "在SqlServer中给User表中增加一条记录" <<endl;
	}
	User* GetUser(int id)
	{
		cout << "在SqlServer中根据ID得到User表中的一条记录" <<endl;
		return NULL;
	}
	WX_DECLARE_DYNAMIC(SqlServerUser);
};
WX_IMPLEMENT_DYNAMIC(SqlServerUser, GETCLASS(IUser));

class SqlServerDepartment : public IDepartment
{
public:
	void Insert(Department* department)
	{
		cout << "在SqlServer中给Department表中增加一条记录" <<endl;
	}
	Department* GetDepartment(int id)
	{
		cout << "在SqlServer中根据ID得到Department表中的一条记录" <<endl;
		return NULL;
	}
	WX_DECLARE_DYNAMIC(SqlServerDepartment);
};
WX_IMPLEMENT_DYNAMIC(SqlServerDepartment, GETCLASS(IDepartment));

// Access DB
class AccessUser : public IUser
{
public:
	void Insert(User* user)
	{
		cout << "在Access中给User表中增加一条记录" <<endl;
	}
	User* GetUser(int id)
	{
		cout << "在Access中根据ID得到User表中的一条记录" <<endl;
		return NULL;
	}
	WX_DECLARE_DYNAMIC(AccessUser);
};
WX_IMPLEMENT_DYNAMIC(AccessUser, GETCLASS(IUser));

class AccessDepartment : public IDepartment
{
public:
	void Insert(Department* department)
	{
		cout << "在Access中给Department表中增加一条记录" <<endl;
	}
	Department* GetDepartment(int id)
	{
		cout << "在Access中根据ID得到Department表中的一条记录" <<endl;
		return NULL;
	}
	WX_DECLARE_DYNAMIC(AccessDepartment);
};
WX_IMPLEMENT_DYNAMIC(AccessDepartment, GETCLASS(IDepartment));

// 简单工厂模式
class DataAccessUseReflect
{
public:
	static IUser* CreateUser()
	{
		STRING className = DBNamePrefix + _T("User");
		INT id = IDFactory();
		TCHAR szName[MAX_PATH];
		_stprintf_s(szName, _T("%d"), id);
		return (IUser*)(g_theKernel.NewNode(className.c_str(), _T("bin"), szName));
	}

	static IDepartment* CreateDepartment()
	{
		STRING className = DBNamePrefix + _T("Department");
		INT id = IDFactory();
		TCHAR szName[MAX_PATH];
		_stprintf_s(szName, _T("%d"), id);
		return (IDepartment*)(g_theKernel.NewNode(className.c_str(), _T("bin"), szName));
	}

protected:
	static INT IDFactory(VOID) { static INT nLastUID = 100; return ++nLastUID; }
private:
	static STRING DBNamePrefix;
};

// 这个可从配置文件中读取
STRING DataAccessUseReflect::DBNamePrefix = _T("Access");

int _tmain(int argc, _TCHAR* argv[])
{
	// 注册类
	g_theKernel.ReisgerClass(GETCLASS(SqlServerUser));
	g_theKernel.ReisgerClass(GETCLASS(SqlServerDepartment));
	g_theKernel.ReisgerClass(GETCLASS(AccessUser));
	g_theKernel.ReisgerClass(GETCLASS(AccessDepartment));

	User user;
	Department dept;
	IUser *pUser = DataAccessUseReflect::CreateUser();
	IDepartment *pDept = DataAccessUseReflect::CreateDepartment();
	pUser->Insert(&user);
	pUser->GetUser(0);
	pDept->Insert(&dept);
	pDept->GetDepartment(0);

	system("pause");
	return 0;
}
