// ntPEVersion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ntPEVersion.h"
#include "stdio.h"

#include "VersionInfo.h"

#include <afx.h>
#include <afxdb.h>
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

//隐藏运行时的dos窗口
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib,"msvcrt.lib")

#if (_MSC_VER < 1300)  
#pragma comment(linker,"/IGNORE:4078")  
#pragma comment(linker,"/OPT:NOWIN98")
#endif 
#define WIN32_LEAN_AND_MEAN

#pragma pack(1)

#ifdef NDEBUG
// /Og (global optimizations), /Os (favor small code), /Oy (no frame pointers)
//#pragma optimize("gsy",on)
#endif // NDEBUG

BOOL CopyVersionInfo(); //设置版本信息


char szHostFileName[MAX_PATH];
char szBindFileName[MAX_PATH];
FILETIME		lpCreationTime;
FILETIME		lpLastAccessTime;
FILETIME		lpLastWriteTime;


void ShowUsage(char *progname)
{
	_tprintf("Query or modify Version Info of PE file.\n");
	_tprintf("USAGE:\n");
	_tprintf("\t%s -s <PathName>\n\tPrints out version numbers of all PEs in Windows system folder.\n\n",progname);
	_tprintf("\t%s -q <FileName>\n\tPrints out version info string tables of a specified PE.\n\n",progname);
	_tprintf("\t%s -h <FileName>\n\tThe PE file whose  version info will be copied.\n\n",progname);
	_tprintf("\t%s -b <FileName>\n\tThe PE file whose  version info will be modified\n\n",progname);
}

BOOL ModifyAttr()
{
	//备份时间
	HANDLE hTimeFile = CreateFile(szBindFileName, GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, NULL); 	
	GetFileTime(hTimeFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	CloseHandle(hTimeFile);
	if(!CopyVersionInfo())
		return FALSE;
	//////////////////////////////////////////////////////////////////////////
	//复原时间
	HANDLE hTrojFile = CreateFile(szBindFileName, 
		GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 	
	SetFileTime(hTrojFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	CloseHandle(hTrojFile); 
	return TRUE;
}

void ShowSystemFilesVersions()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	
	TCHAR szBuf[MAX_PATH];
	::GetSystemDirectory(szBuf, MAX_PATH);
	CString strSystemFolder = szBuf;
	
	hFind = FindFirstFile(strSystemFolder + "\\*.dll", &FindFileData);
	
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		printf ("Invalid File Handle. Get Last Error reports %d\n", GetLastError ());
	} 
	else 
	{
		do
		{
			CString strModulePath = strSystemFolder + "\\" + FindFileData.cFileName;
			
			const CVersionInfo vi(strModulePath);
			
			if (vi.IsValid())
			{
				_tprintf(_T("%s\t%s\n"), FindFileData.cFileName, vi["FileVersion"]);
			}
			
		}
		while (FindNextFile(hFind, &FindFileData));
		
		FindClose(hFind);
	}
}


BOOL CopyVersionInfo()
{
	//用宿主PE文件的版本信息设置最终生成PE文件的版本信息
	CVersionInfo vihost(szHostFileName);
	CVersionInfo viBind(szBindFileName);//
	VS_FIXEDFILEINFO vshostinfo;
	vshostinfo=vihost.GetFixedFileInfo();
	viBind.SetFileVersion(vshostinfo.dwFileVersionMS,vshostinfo.dwFileVersionLS);
	//其他信息
	POSITION posTable = vihost.GetStringFileInfo().GetFirstStringTablePosition();
	while (posTable)
	{
		const CStringTable &st = *vihost.GetStringFileInfo().GetNextStringTable(posTable);				
		POSITION posString = st.GetFirstStringPosition();				
		while (posString)
		{
			const CVersionInfoString &vistr = *st.GetNextString(posString);
			CString str;
			viBind[vistr.GetKey()] = vistr.GetValue();
			viBind.Save();
		}
	}
	return TRUE;
}

void TestVersionInfoLib(int argc, TCHAR* argv[], TCHAR* envp[])
{
	if (2 == argc)
	{
		if (!_tcscmp(argv[1], _T("-s")))
		{
			ShowSystemFilesVersions();
		}
		else
			ShowUsage(argv[0]);
	}
	else if (3 == argc)
	{
		if (!_tcscmp(argv[1], _T("-q")))
		{
			// 2nd argument is the file path
			CString strFilePath(argv[2]);
			
			const CVersionInfo vi(strFilePath);
			if (vi.IsValid())
			{
				POSITION posTable = vi.GetStringFileInfo().GetFirstStringTablePosition();
				while (posTable)
				{
					const CStringTable &st = *vi.GetStringFileInfo().GetNextStringTable(posTable);
					
					_tprintf(_T("String table %s\n------------------------------\n"), st.GetKey());
					
					POSITION posString = st.GetFirstStringPosition();
					
					while (posString)
					{
						const CVersionInfoString &vistr = *st.GetNextString(posString);
						_tprintf(_T("%s=%s\n"), vistr.GetKey(), vistr.GetValue());
					}
					_tprintf(_T("------------------------------\n"));
				}
			}
			else
			{
				_tprintf(_T("Failed to get module version information for %s\n"), strFilePath);
			}
		}
		else
			ShowUsage(argv[0]);
		
	}
	else if(5 == argc)
	{ 

		if (!_tcscmp(argv[1], _T("-h"))&&!_tcscmp(argv[3], _T("-b")))
		{
			strcpy(szHostFileName,argv[2]);
			strcpy(szBindFileName,argv[4]);
			ModifyAttr();
		}
		else if(!_tcscmp(argv[3], _T("-h"))&&!_tcscmp(argv[1], _T("-b")))
		{
			strcpy(szHostFileName,argv[4]);
			strcpy(szBindFileName,argv[2]);
			ModifyAttr();
		}
		else
			ShowUsage(argv[0]);
	}
	else
		ShowUsage(argv[0]);	
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		printf("Fatal Error: MFC initialization failed");
		nRetCode = 1;
	}
	else
	{
		TestVersionInfoLib(argc, argv, envp);
	}

	return nRetCode;
}























