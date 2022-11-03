// This is the main project file for VC++ application project 
// generated using an application wizard.

#include "stdafx.h"

#using <mscorlib.dll>
#using <..\Ex32a\debug\Ex32a.dll>
#include <tchar.h>

using namespace System;
using namespace Ex32a;

__gc class CDelegateHolder {
public:
	static void DelegateFn(String* str) {
		Console::WriteLine(str);
	}
};

void UseValueStruct() {
	Console::WriteLine("Working with AManagedValueStruct");
	AManagedValueStruct amvs;
	Console::WriteLine(amvs.m_str);
	amvs.Method1();

}

void UseGcStruct() {
	Console::WriteLine("Working with AManagedGcStruct");
	AManagedGcStruct *amgcs;
	amgcs= new AManagedGcStruct();
	Console::WriteLine(amgcs->m_str);
	amgcs->Method1();
}

// This is the entry point for this application
int _tmain(void)
{
    // TODO: Please replace the sample code below with your own.
    Console::WriteLine("Creating and exercising an instance of AManagedClass");
	AManagedClass *amc = new AManagedClass();
	Console::WriteLine("Filling array");
	amc->FillArray();
	amc->ShowArray();

	Console::WriteLine();

	Console::WriteLine("Creating and using a delegate");
	CDelegateHolder *dh;
	dh = new CDelegateHolder();
	AManagedDelegate *amd;
	amd = new AManagedDelegate(dh, dh->DelegateFn);
	amc->UseDelegate(amd);
	Console::WriteLine();

	Console::WriteLine("Talking to the object through IAManagedInterface");
	IAManagedInterface *ami;
	ami = amc;
	ami->MethodA();
	ami->MethodB();

	Console::WriteLine();
	UseGcStruct();

	Console::WriteLine();
	UseValueStruct();

	GC::Collect();

	return 0;
}