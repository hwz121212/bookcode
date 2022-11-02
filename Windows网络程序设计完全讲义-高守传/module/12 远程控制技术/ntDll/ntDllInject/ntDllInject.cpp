// ntDllInject.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ntDllInject.h"



//-------------------------------------------------------
// shared data 

#pragma data_seg (".shared")

DllRWSData  gRwsData={0,L'\0'};

#pragma data_seg ()

#pragma comment(linker,"/SECTION:.shared,RWS")



#define lenof(x) ( sizeof (x) / sizeof ((x)[0]) )

DWORD __stdcall GetCmdArg( DllRWSData *c );



BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
    if(ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		GetCmdArg(&gRwsData);
	}
	return TRUE;
}

// The whole shebang makes a number of assumptions:
// -- target process is a Win32 process
// -- kernel32.dll loaded at same address in each process (safe)
// -- GetCmdArg() shorter than ?
// -- GetCmdArg() does not rely on the C/C++ runtime
// -- /GZ is _not_ used. (If it is, the compiler generates calls
//    to functions which are not injected into the target. Oops!
DWORD __stdcall GetCmdArg( DllRWSData *c )
{
	const wchar_t *src;
	wchar_t *tgt, *end;
	
	src =GetCommandLineW();
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



