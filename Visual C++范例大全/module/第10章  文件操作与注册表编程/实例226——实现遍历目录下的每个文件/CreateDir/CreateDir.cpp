// CreateDir.cpp : Defines the entry point for the console application.
//// ���ߣ�xiaotaoliang   xiaotaoliang@sina.com

//-------------------------------------------------------------------
//	ʹ�÷���:�������������� C:\test1\test2\test3
//-------------------------------------------------------------------

#include "stdio.h"
#include "util.h"


int main(int argc, char* argv[])
{
	if(argc<2)
	{
		printf("ʹ�ã�CreateDir dirname\n");
		return 1;
	}
	CUTil util;
	if(util.CreateDir(argv[1]))
	{
		printf("ok.����Ŀ¼%s\n",argv[1]);
	}
	else
	{
		printf("����Ŀ¼%sʧ��\n",argv[1]);
	}
	return 0;
}

