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
	//������Ϣ
	if ( argc == 1 )
	{
		wprintf ( L"usage: remthread dwPid [dwPid ...]\n");
		wprintf (L"Reports the command lines of the specified processes.\n");
		wprintf (L"Use \"-1\" to have the program look at itself.\n");
		return 1;
	}
	//��Ȩ
	EnableDebugPriv();
	for ( i = 1; i < argc; ++ i )
	{
		dwPid=_wtol(argv[i]);
		if ( dwPid == (DWORD) -1 )
			dwPid = GetCurrentProcessId();
		wprintf ( L"dwPid=%u\n",dwPid);
		//�õ�Զ�̽��̵�HANDLE
		hProcess= OpenProcess( PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
			PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwPid );
		//�߳�ע�룬������ע����̵��������ַ�����ӡ��
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
			//ָ�����ڽ��մ�����Ϣ�Ļ�����
			HLOCAL hlocal = NULL;
			//����������������
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
	//DLL·��szLibPath��Զ�̽����еĵ�ַ;
	void*  pLibRemote = 0;
	//������ģ��Ļ�ַ
	DWORD  hLibModule = 0;	
	
	HMODULE hKernel32 = ::GetModuleHandle(L"Kernel32");
	//��ȡDLLȫ·����
	wcscpy(szLibPath,DLL_FULLPATH);	
	
	//��Զ�̽���ΪDLL���ַ���ռ�
	//��szLibPathд��Զ�̽��̿ռ�
	pLibRemote = ::VirtualAllocEx( hProcess, NULL, sizeof(szLibPath), MEM_COMMIT, PAGE_READWRITE );
	if( pLibRemote == NULL )
		return FALSE;
	::WriteProcessMemory(hProcess, pLibRemote, (void*)szLibPath,sizeof(szLibPath),NULL);
	
	
	//ͨ��CreateRemoteThread��LoadLibrary��DLL���ص�Զ�̽��� 
	hThread = ::CreateRemoteThread( hProcess, NULL, 0,	
		(LPTHREAD_START_ROUTINE) ::GetProcAddress(hKernel32,"LoadLibraryW"), 
		pLibRemote, 0, NULL );
	if( hThread == NULL )
		goto JUMP;
	//�ȴ�Զ���߳̽�����WaitForSingleObject�������ȴ�LoadLibrary����
	::WaitForSingleObject( hThread, INFINITE );
	
	//ȡ��Զ���̵߳Ľ����루GetExitCodeThtread������LoadLibraryW�ķ���ֵ
	//DLL���غ�Ļ���ַ��HMODULE��
	::GetExitCodeThread( hThread, &hLibModule);
	::CloseHandle( hThread );
	
JUMP:	
	::VirtualFreeEx( hProcess, pLibRemote, sizeof(szLibPath), MEM_RELEASE );
	if( hLibModule == NULL )
		return FALSE;
	
	
	//ͨ��CreateRemoteThread��FreeLibraryԶ�̽���ж��DLL
	hThread = ::CreateRemoteThread( hProcess,
		NULL, 0,
		(LPTHREAD_START_ROUTINE) ::GetProcAddress(hKernel32,"FreeLibrary"),
		(void*)hLibModule,
		0, NULL );
	if( hThread == NULL )
		return FALSE;
	//�ȴ��̵߳Ľ���
	::WaitForSingleObject( hThread, INFINITE );
	::GetExitCodeThread( hThread, &hLibModule );
	::CloseHandle( hThread );
	
	//����Զ��FreeLibrary�Ľ�����
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


