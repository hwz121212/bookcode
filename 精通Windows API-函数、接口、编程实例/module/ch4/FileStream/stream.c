/* ************************************
*《精通Windows API》 
* 示例代码
* current_dir.c
* 4.3.4	获取当前目录、获取程序所在的目录、获取模块路径
* 2007年10月
**************************************/

/* 头文件　*/
#include <windows.h>
#include <stdio.h>

//wsprintf连接
#pragma comment (lib, "User32.lib")

/* ************************************
* int main(void)
* 功能	演示使用设置获取当前路径
*		演示获取模块路径
*
* 参数	无
*
* 2007年10月
*
**************************************/
int AddStreamToFile(LPSTR szFilePath, 
					LPSTR szStreamName,
					PVOID pStreamData,
					DWORD dwStreamDataSize
					)
{
	CHAR szStreamPath[MAX_PATH];
	HANDLE hStream;
	DWORD dwWritted;
	wsprintf(szStreamPath,"%s:%s",szFilePath,szStreamName);

	hStream = CreateFile(szStreamPath, 
		GENERIC_WRITE,
		0, 
		NULL,
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if(hStream == INVALID_HANDLE_VALUE)
	{
		printf("create file error: %d\n",GetLastError());
		return 1;
	}
	if(!WriteFile(hStream,pStreamData,dwStreamDataSize,&dwWritted,NULL))
	{
		printf("write file error: %d\n",GetLastError());
		CloseHandle(hStream);
		return 1;
	}
	printf("writted %d byte\n",dwWritted);
	CloseHandle(hStream);
	return 0;

}
int ReadStreamData(LPSTR szStreamPath, 
				   LPVOID lpDataBuffer,
				   DWORD dwBufferSize
				   )
{

	HANDLE hStream;
	DWORD dwRead;

	DWORD dwDataSize;


	hStream = CreateFile(szStreamPath, 
		GENERIC_READ,
		0, 
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if(hStream == INVALID_HANDLE_VALUE)
	{
		printf("open stream error: %d\n",GetLastError());
		return 1;
	}
	dwDataSize = GetFileSize(hStream,NULL);
	printf("stream data size is %d, is %s than buffer's\n",
		dwDataSize,(dwDataSize > dwBufferSize ? "larger":"not larger"));
	if(!ReadFile(hStream,lpDataBuffer,dwBufferSize,&dwRead,NULL))
	{
		printf("read file error: %d\n",GetLastError());
	}
	printf("read %d byte\n",dwRead);
	CloseHandle(hStream);
	return 0;

}
//DWROD EnumStreams2k3(LPWSTR szFilePath)
//{
//	WIN32_FIND_STREAM_DATA wfsd;
//	HANDLE hFind;
//	hFind = FindFirstStreamW(szFilePath,
//		FindStreamInfoStandard,
//		&wfsd,
//		0);
//	if(hFind == INVALID_HANDLE_VALUE)
//	{
//		printf("find stream error: %d",GetLastError());
//		return 1;
//	}
//	do
//	{
//
//	}
//	return 0;
//}

LPSTR szStreamData1 = "THIS IS A STREAM DATA";
BYTE lpStreamData2[10] = {0x00,0x01,0x02,0x03};

int main(void)
{
	DWORD i=0;

	DWORD dwData1Len = lstrlen(szStreamData1);

	AddStreamToFile("test.txt","s1",szStreamData1,dwData1Len);
	AddStreamToFile("test.txt","s2",lpStreamData2,10);
	ZeroMemory(szStreamData1,dwData1Len);
	ZeroMemory(lpStreamData2,10);
	ReadStreamData("test.txt:s1",szStreamData1,dwData1Len);
	printf("read %d bytes form test.txt:s1: \"%s\"\n",
		dwData1Len, szStreamData1);
	ReadStreamData("test.txt:s2",lpStreamData2,10);
	printf("read 10 bytes form test.txt:s2: ");
	for(; i<10; i++)
	{
		printf("0x%#02d ",lpStreamData2[i]);
	}
	return 0;
}