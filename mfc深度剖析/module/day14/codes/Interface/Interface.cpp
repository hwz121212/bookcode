// Interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/////////////>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include<objbase.h>
//#define interface struct
interface IMath{
	public:
	virtual	int Add(int nAdd1,int nAdd2)=0;
	virtual	int Sub(int nSub1,int nSub2)=0;

};

class CIMath:public IMath{
public:
	virtual	int Add(int nAdd1,int nAdd2);
	virtual	int Sub(int nSub1,int nSub2);
};
int CIMath::Add(int nAdd1,int nAdd2){
	return nAdd1+nAdd2;
}
int CIMath::Sub(int nSub1,int nSub2){
	return nSub1-nSub2;
}
class CIMath1:public IMath{
public:
	virtual	int Add(int nAdd1,int nAdd2);
	virtual	int Sub(int nSub1,int nSub2);
};
int CIMath1::Add(int nAdd1,int nAdd2){
	return nAdd1+nAdd2+100;
}
int CIMath1::Sub(int nSub1,int nSub2){
	return nSub1-nSub2-100;
}

IMath* CreateInstance(){
	return new CIMath;
}

//service function model
/////////////>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//using function model

typedef IMath*(*INSTANCE)()	;//INSTANCE function pointer

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
	CIMath math;
	int nAdd=math.Add(100,100);
	printf("%d\n",nAdd);

	//use interface
	IMath* pMath=GetMath();
	nAdd=pMath->Add(100,100);
	printf("%d\n",nAdd);
	getchar();
	return 0;
}

