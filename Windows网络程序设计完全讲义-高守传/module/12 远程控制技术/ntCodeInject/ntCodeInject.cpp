// ntCodeInject.cpp : Defines the entry point for the console application.
//

// demonstrates getting the command line of another process
// requires PROCESS_CREATE_THREAD, PROCESS_VM_OPERATION,
// PROCESS_VM_WRITE, PROCESS_VM_READ to the target, or the
// SeDebugPrivilege

// *** You *must* remove "/GZ" from the debug build settings ***
// (If you use my (felixk's) project file, this has already happened)

#include "stdafx.h"


#define lenof(x) ( sizeof (x) / sizeof ((x)[0]) )

typedef const wchar_t *(__stdcall *fnGclW)( void );

const DWORD MAXINJECTSIZE =4096;
const UINT  COMMANDBUFFER =200;

struct DllRWSData
{
	DWORD dwLastError; //远程线程的最后一个错误码
	fnGclW pGclW; //GetCommandLineW()的地址
	wchar_t wstr[COMMANDBUFFER]; //命令行缓冲区
};


//设置调式权限SeDebugPrivilege
void EnableDebugPriv( void );
//将GetCmdArg()注入目标进程
BOOL InjectCode( HANDLE h, wchar_t* str );
//注入代码
DWORD __stdcall GetCmdArg( DllRWSData *c );


int wmain( int argc, wchar_t *argv[])
{
	int i;
	DWORD dwPid;
	HANDLE hProcess;
	wchar_t str[COMMANDBUFFER];

	if ( argc == 1 )
	{
		wprintf ( L"usage: remthread dwPid [dwPid ...]\n");
		wprintf (L"Reports the command lines of the specified processes.\n");
		wprintf (L"Use \"-1\" to have the program look at itself.\n");
		return 1;
	}

	//设置调式权限
	EnableDebugPriv();
	for ( i = 1; i < argc; ++ i )
	{
		dwPid=_wtol(argv[i]);
		//若进程id为-1则是查看本进程的命令行
		if ( dwPid == (DWORD) -1 )
			dwPid = GetCurrentProcessId();
		wprintf ( L"dwPid=%u\n",dwPid);
		//打开目标进程
		hProcess= OpenProcess( PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
			PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwPid );
		if (hProcess!= 0 )
		{
			//向目标进程注入代码，并打印输出结果
			if( InjectCode(hProcess, str))
				wprintf (L" \n %s",str);
			CloseHandle(hProcess);
		}
		else
			wprintf ( L"open failed, dwLastError=%u\n",GetLastError());
	}

	return 0;
}



void EnableDebugPriv( void )
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if ( ! OpenProcessToken( GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
	{
		wprintf( L"OPT() failed, dwLastError = %u", 
			L" SeDebugPrivilege is not available.",GetLastError() );
		return;
	}

	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		wprintf(L"LPV() failed, dwLastError = %u"
			L" SeDebugPrivilege is not available.",GetLastError());
		CloseHandle( hToken );
		return;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
		wprintf(L"ATP() failed, dwLastError =%u "
			L" SeDebugPrivilege is not available.",GetLastError());

	CloseHandle( hToken );
}



BOOL InjectCode( HANDLE h, wchar_t* str)
{
	HANDLE ht = 0;
	void *p = 0;
	DllRWSData *c = 0;
	BOOL result = FALSE;
	DWORD rc;
	HMODULE hk32 = 0;
	DllRWSData localCopy;

	//为执行代码分配内存
	p = VirtualAllocEx( h, 0, MAXINJECTSIZE, MEM_COMMIT, PAGE_EXECUTE_READWRITE );
	if ( p == 0 )
	{
		wprintf( L"VAE() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	}
	//为执行代码所需的数据结构分配内存
	c = (DllRWSData *) VirtualAllocEx( h, 0, sizeof DllRWSData, MEM_COMMIT, PAGE_READWRITE );
	if ( c == 0 )
	{
		wprintf( L"VAE() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	}

	//将函数复制到目标进程
	if ( ! WriteProcessMemory( h, p, &GetCmdArg, MAXINJECTSIZE, 0 ) )
	{
		wprintf( L"WPM() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	}

	//初始化远程数据结构
	hk32 = LoadLibrary(L"kernel32.dll" );
	if ( hk32 == 0 )
	{
		wprintf( L"LL() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	}
	localCopy.dwLastError = 0;
	localCopy.pGclW = (fnGclW) GetProcAddress( hk32, "GetCommandLineW" );
	if ( localCopy.pGclW == 0 )
	{
		wprintf( L"GPA() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	}
	FreeLibrary( hk32 );
	hk32 = 0;
	localCopy.wstr[0] = L'\0';
	//将数据结构写到远程进程
	if ( ! WriteProcessMemory( h, c, &localCopy, sizeof localCopy, 0 ) )
	{
		wprintf( L"WPM() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	}

	//创建远程线程 CreateRemoteThread()
	ht = CreateRemoteThread( h, 0, 0, (DWORD (__stdcall *)( void *)) p, c, 0, &rc );
	if ( ht == NULL )
	{
		wprintf( L"CRT() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	}

	rc = WaitForSingleObject( ht, 3000 );
	switch ( rc )
	{
	case WAIT_TIMEOUT:
		wprintf(L"WFSO() timed out. Odd!");
		goto cleanup;
	case WAIT_FAILED:
		wprintf( L"WFSO() failed, dwLastError =%u ",GetLastError()) ;
		goto cleanup;
	case WAIT_OBJECT_0:
		//读取远程线程的执行结果
		if ( ! ReadProcessMemory( h, c, &localCopy, sizeof localCopy, 0 ) )
		{
			wprintf( L"RPM() failed, dwLastError =%u ",GetLastError()) ;
			goto cleanup;
		}
		if ( localCopy.dwLastError == 0 )
		{
			memcpy(str, localCopy.wstr,sizeof(localCopy.wstr));
			result = TRUE;
			wprintf(L"successfully buggered.");
		}
		else
			wprintf( L"Remote thread failed, dwLastError =%u ",localCopy.dwLastError);
		break;
	default:
		wprintf( L"WFSO() returned a surprise! rc =%u,"
			L"dwLastError =%u ",rc,GetLastError()) ;
		break;
	}

cleanup:
	CloseHandle( ht );
	if ( p != 0 )
		VirtualFreeEx( h, p, 0, MEM_RELEASE );
	if ( c != 0 )
		VirtualFreeEx( h, c, 0, MEM_RELEASE );
	if ( hk32 != 0 )
		FreeLibrary( hk32 );

	return result;
}


// The whole shebang makes a number of assumptions:
// -- target process is a Win32 process
// -- kernel32.dll loaded at same address in each process (safe)
// -- GetCmdArg() shorter than MAXINJECTSIZE
// -- GetCmdArg() does not rely on the C/C++ runtime
// -- /GZ is _not_ used. (If it is, the compiler generates calls
//    to functions which are not injected into the target. Oops!
DWORD __stdcall GetCmdArg( DllRWSData *c )
{
	const wchar_t *src;
	wchar_t *tgt, *end;

	src = c->pGclW();
	tgt = &c->wstr[0];
	end = &c->wstr[lenof( c->wstr ) - 1];
	if ( src == 0 || tgt == 0 || end == 0 )
	{
		c->dwLastError = 998;
		return 0;
	}

	for ( ;	*src != L'\0' && tgt < end; ++ src, ++ tgt )
		*tgt = *src;
	*tgt = L'\0';
	c->dwLastError = 0;

	return 0;
}


