// CreateDir.cpp : Defines the entry point for the console application.
//// 作者：xiaotaoliang   xiaotaoliang@sina.com

//-------------------------------------------------------------------
//	使用方法:在命令行中输入 C:\test1\test2\test3
//-------------------------------------------------------------------

#include "stdio.h"
#include "util.h"


int main(int argc, char* argv[])
{
	if(argc<2)
	{
		printf("使用：CreateDir dirname\n");
		return 1;
	}
	CUTil util;
	if(util.CreateDir(argv[1]))
	{
		printf("ok.建立目录%s\n",argv[1]);
	}
	else
	{
		printf("建立目录%s失败\n",argv[1]);
	}
	return 0;
}

