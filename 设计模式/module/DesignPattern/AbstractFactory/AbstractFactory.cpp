// AbstractFactory.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/17
	FILENAME:	AbstractFactory.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	���󹤳�ģʽ
		����������ģʽ�в�ֹһ���Ʒʱ����Operation��һ���Ʒ�����ͱ���˳��󹤳�ģʽ
		���磬�����������
		��ʱ��IFactory�ӿ��д������в�Ʒ��User��Department���ĳ��󷽷���
*********************************************************************/

#include "stdafx.h"
#include "Reflection/tClass.h"
#include "Reflection/tKernel.h"
#include "Reflection/BasicType.h"
#include <iostream>

using namespace std;

/**
	���󹤳�ģʽ
*/

//// User���ṹ
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
//// Department��ṹ
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
//// �����
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
//		cout << "��SqlServer�и�User��������һ����¼" <<endl;
//	}
//	User* GetUser(int id)
//	{
//		cout << "��SqlServer�и���ID�õ�User���е�һ����¼" <<endl;
//		return NULL;
//	}
//};
//
//class SqlServerDepartment : public IDepartment
//{
//public:
//	void Insert(Department* department)
//	{
//		cout << "��SqlServer�и�Department��������һ����¼" <<endl;
//	}
//	Department* GetDepartment(int id)
//	{
//		cout << "��SqlServer�и���ID�õ�Department���е�һ����¼" <<endl;
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
//		cout << "��Access�и�User��������һ����¼" <<endl;
//	}
//	User* GetUser(int id)
//	{
//		cout << "��Access�и���ID�õ�User���е�һ����¼" <<endl;
//		return NULL;
//	}
//};
//
//class AccessDepartment : public IDepartment
//{
//public:
//	void Insert(Department* department)
//	{
//		cout << "��Access�и�Department��������һ����¼" <<endl;
//	}
//	Department* GetDepartment(int id)
//	{
//		cout << "��Access�и���ID�õ�Department���е�һ����¼" <<endl;
//		return NULL;
//	}
//};
//
//// ���������
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
	ʹ�÷������&�򵥹���ģʽ���Ľ����󹤳�ģʽ
*/

tKernel g_theKernel;

// User���ṹ
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

// Department��ṹ
class Department
{
public:
	int GetID() { return _id; }
	void SetID(int id) { _id = id; }

private:
	int _id;
};

// ����ࣨ����tNodeʵ��C++���䣩
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
		cout << "��SqlServer�и�User��������һ����¼" <<endl;
	}
	User* GetUser(int id)
	{
		cout << "��SqlServer�и���ID�õ�User���е�һ����¼" <<endl;
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
		cout << "��SqlServer�и�Department��������һ����¼" <<endl;
	}
	Department* GetDepartment(int id)
	{
		cout << "��SqlServer�и���ID�õ�Department���е�һ����¼" <<endl;
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
		cout << "��Access�и�User��������һ����¼" <<endl;
	}
	User* GetUser(int id)
	{
		cout << "��Access�и���ID�õ�User���е�һ����¼" <<endl;
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
		cout << "��Access�и�Department��������һ����¼" <<endl;
	}
	Department* GetDepartment(int id)
	{
		cout << "��Access�и���ID�õ�Department���е�һ����¼" <<endl;
		return NULL;
	}
	WX_DECLARE_DYNAMIC(AccessDepartment);
};
WX_IMPLEMENT_DYNAMIC(AccessDepartment, GETCLASS(IDepartment));

// �򵥹���ģʽ
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

// ����ɴ������ļ��ж�ȡ
STRING DataAccessUseReflect::DBNamePrefix = _T("Access");

int _tmain(int argc, _TCHAR* argv[])
{
	// ע����
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
