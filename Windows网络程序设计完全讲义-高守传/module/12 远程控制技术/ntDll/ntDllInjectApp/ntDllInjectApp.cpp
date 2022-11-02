// ntDllInjectApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>
#include "..\ntDllInject\ntDllInject.h"

#define DLL_FULLPATH  L"D:\\pratice\\ntDll\\ntDllInjectApp\\ntDllInject.dll"

int  InjectDll(HANDLE hProcess);
void EnableDebugPriv( void );



int wmain( int argc, wchar_t*argv[])
{
	int i;
	DWORD dwPid;
	HANDLE hProcess;
	//帮助信息
	if ( argc == 1 )
	{
		wprintf ( L"usage: remthread dwPid [dwPid ...]\n");
		wprintf (L"Reports the command lines of the specified processes.\n");
		wprintf (L"Use \"-1\" to have the program look at itself.\n");
		return 1;
	}
	//提权
	EnableDebugPriv();
	for ( i = 1; i < argc; ++ i )
	{
		dwPid=_wtol(argv[i]);
		if ( dwPid == (DWORD) -1 )
			dwPid = GetCurrentProcessId();
		wprintf ( L"dwPid=%u\n",dwPid);
		//得到远程进程的HANDLE
		hProcess= OpenProcess( PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
			PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwPid );
		//线程注入，并将被注入进程的命令行字符串打印出
		if (hProcess!= 0 )
		{
			InjectDll(hProcess);
			wprintf (L"%s\n",gRwsData.wstr);
			CloseHandle(hProcess);
		}
		else
		{
			DWORD dwError =GetLastError();
			wprintf ( L"open failed, ErrorCode=0x%x\n",dwError);
			//指向用于接收错误信息的缓冲区
			HLOCAL hlocal = NULL;
			//错误代码的文字描述
			BOOL fOk = FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
				NULL, dwError, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (PTSTR) &hlocal, 0, NULL);
			if (hlocal != NULL)
			{
				wprintf ( L"Error Reason: %s\n",(PCWSTR) LocalLock(hlocal));
				LocalFree(hlocal);
			}
         
		}
	}
	
	return 0;
}

//-----------------------------------------------
//InjectDll
//		Return value:	1 - success;
//						0 - failure;
//
int InjectDll( HANDLE hProcess )
{
	HANDLE hThread;
	wchar_t   szLibPath [_MAX_PATH];
	//DLL路径szLibPath在远程进程中的地址;
	void*  pLibRemote = 0;
	//所加载模块的基址
	DWORD  hLibModule = 0;	
	
	HMODULE hKernel32 = ::GetModuleHandle(L"Kernel32");
	//获取DLL全路径名
	wcscpy(szLibPath,DLL_FULLPATH);	
	
	//在远程进程为DLL名字分配空间
	//将szLibPath写入远程进程空间
	pLibRemote = ::VirtualAllocEx( hProcess, NULL, sizeof(szLibPath), MEM_COMMIT, PAGE_READWRITE );
	if( pLibRemote == NULL )
		return FALSE;
	::WriteProcessMemory(hProcess, pLibRemote, (void*)szLibPath,sizeof(szLibPath),NULL);
	
	
	//通过CreateRemoteThread和LoadLibrary将DLL加载到远程进程 
	hThread = ::CreateRemoteThread( hProcess, NULL, 0,	
		(LPTHREAD_START_ROUTINE) ::GetProcAddress(hKernel32,"LoadLibraryW"), 
		pLibRemote, 0, NULL );
	if( hThread == NULL )
		goto JUMP;
	//等待远程线程结束（WaitForSingleObject），即等待LoadLibrary返回
	::WaitForSingleObject( hThread, INFINITE );
	
	//取回远程线程的结束码（GetExitCodeThtread），即LoadLibraryW的返回值
	//DLL加载后的基地址（HMODULE）
	::GetExitCodeThread( hThread, &hLibModule);
	::CloseHandle( hThread );
	
JUMP:	
	::VirtualFreeEx( hProcess, pLibRemote, sizeof(szLibPath), MEM_RELEASE );
	if( hLibModule == NULL )
		return FALSE;
	
	
	//通过CreateRemoteThread和FreeLibrary远程进程卸载DLL
	hThread = ::CreateRemoteThread( hProcess,
		NULL, 0,
		(LPTHREAD_START_ROUTINE) ::GetProcAddress(hKernel32,"FreeLibrary"),
		(void*)hLibModule,
		0, NULL );
	if( hThread == NULL )
		return FALSE;
	//等待线程的结束
	::WaitForSingleObject( hThread, INFINITE );
	::GetExitCodeThread( hThread, &hLibModule );
	::CloseHandle( hThread );
	
	//返回远程FreeLibrary的结束码
	return hLibModule;
}

void EnableDebugPriv( void )
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	
	if ( ! OpenProcessToken( GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
	{
		wprintf( L"OPT() failed, ErrorCode = %u", 
			L" SeDebugPrivilege is not available.",GetLastError());
		return;
	}
	
	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		wprintf(L"LPV() failed, ErrorCode = %u"
			L" SeDebugPrivilege is not available.",GetLastError());
		CloseHandle( hToken );
		return;
	}
	
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	
	
	if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
	{
		wprintf(L"ATP() failed, ErrorCode =%u "
		L" SeDebugPrivilege is not available.",GetLastError());
	}
	
	CloseHandle( hToken );
}


