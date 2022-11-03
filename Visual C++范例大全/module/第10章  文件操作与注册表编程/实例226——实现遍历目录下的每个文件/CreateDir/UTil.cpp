// UTil.cpp: implementation of the CUTil class.
// 作者：xiaotaoliang   xiaotaoliang@sina.com
//////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "UTil.h"

#include <string>
#include <list>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUTil::CUTil()
{

}

CUTil::~CUTil()
{

}

bool CUTil::CreateDir(char *dir)
{	

	list<string> dirStack;
	
	string tmp = dir;
	
	dirStack.push_front(tmp);

	int i = tmp.rfind("\\");

	//从后面往前找"\\"，检查是否存在目录。
	while(i>0)
	{			
		tmp = tmp.substr(0,i);
		if(DirExists(tmp.c_str()))break;
		dirStack.push_front(tmp);
		i = tmp.rfind("\\",i);		
	}
	
	if(i<0 && (":" != tmp.substr(tmp.length()-1,1)))
		return false;		//错误的目录格式
	
	try
	{
		for(list<string>::iterator it=dirStack.begin();
			it!=dirStack.end();it++)
		{
			::CreateDirectory((*it).c_str(),NULL);
		}
	}
	catch(...)
	{
		return false;			
	}

	return true;
}

bool CUTil::DirExists(const char *dir)
{
	bool tf;
	WIN32_FIND_DATA fd; 
    HANDLE hFind = FindFirstFile(dir, &fd); 
    if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
    { 
		tf = true;
    } 
	else
	{
		tf = false;
	}
    FindClose(hFind); 
	return tf;
}
