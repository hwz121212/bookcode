// UseDllInterface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Dllinterface/math.h"
typedef IMath*(*INSTANCE)()	;//INSTANCE function pointer
//typedef IMath* (*)()  INSTANCE;
IMath* GetMath(){
	//Load dll
	HMODULE hDll=LoadLibrary("DllInterface.dll");
	INSTANCE Instance=(INSTANCE)GetProcAddress(
			hDll,"CreateInstance"
		);
	IMath* pMath=Instance();
	return pMath;
}
int main(int argc, char* argv[])
{
	IMath* pMath=GetMath();
	pMath->AddRef();
	int nAdd=pMath->Add(100,100);
	pMath->Release();
	printf("%d\n",nAdd);
	//һ�����̵Ķ���˽�е�,�����������
//	delete pMath;	error
	getchar();
	return 0;
}

