
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the NTDLLINJECT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NTDLLINJECT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef NTDLLINJECT_EXPORTS
#define NTDLLINJECT_API __declspec(dllexport)
#else
#define NTDLLINJECT_API __declspec(dllimport)
#endif

const UINT  COMMANDBUFFER =200;

//////////////////////////////////////////////
struct DllRWSData
{
	DWORD dwLastError; // last error from remote thread
	wchar_t wstr[COMMANDBUFFER]; // the command line buffer
};

extern NTDLLINJECT_API DllRWSData gRwsData;