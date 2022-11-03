// Ex32a.h

#pragma once

using namespace System;

#using <System.DLL>
#using <System.Drawing.DLL> 
#using <System.Windows.Forms.DLL>
#using <System.Runtime.Remoting.DLL>

using namespace System;
using namespace System::Collections;

namespace Ex32a
{

// C++ Assembly full of managed types...
public __value enum DaysOfTheWeek {
	Monday, 
	Tuesday, 
	Wednesday, 
	Thursday, 
	Friday, 
	Saturday, 
	Sunday
};

public __value struct AManagedValueStruct {
	int m_n;
	double m_x;
	String* m_str;

	AManagedValueStruct() {
		m_n = 0;
		m_x = 1.1;
		m_str=new String("Hi there from AManagedValueStruct");
	}

	void Method1() {
		Console::WriteLine("Called AManagedValueStruct::Method1()");
	}
};

public __gc struct AManagedGcStruct {
	AManagedGcStruct() {
		m_str=new String("Hi there from AManagedGcStruct");
	}
	~AManagedGcStruct() {
		System::Console::WriteLine("AManagedStruct Going Away\n");
	}
	void Method1() {
		Console::WriteLine("Called AManagedGcStruct::Method1()");
	}
	int m_n;
	double m_x;
	String* m_str;
};

public __gc __interface IPerson {
	void Eat();
	void Sleep();
	void Work();
};

public __gc class SoftwareDeveloper : public IPerson{
	~SoftwareDeveloper() {
		System::Console::WriteLine("Finalize called for SoftwareDeveloper");
	}
	void Eat() {
		System::Console::WriteLine("Eat pizza");
	}
	void Sleep() {
		System::Console::WriteLine("Sleep during the day");
	}
	void Work() {
		System::Console::WriteLine("Work during the night");
	}
};

public __gc class DotCOMVP : public IPerson {
	~DotCOMVP() {
		System::Console::WriteLine("Finalize called for DotCOMVP");
	}
	void Eat() {
		System::Console::WriteLine("Eat to Schmooze");
	}
	void Sleep() {
		System::Console::WriteLine("Never sleep");
	}
	void Work() {
		System::Console::WriteLine("Work to get Venture Capital");
	}
};

public __gc class Bum : public IPerson {
	~Bum() {
		System::Console::WriteLine("Finalize called for Bum");
	}
	void Eat() {
		System::Console::WriteLine("Eat sporadically");
	}
	void Sleep() {
		System::Console::WriteLine("Sleep whenever possible");
	}
	void Work() {
		System::Console::WriteLine("Work?");
	}
};

public __delegate void AManagedDelegate(String* strMessage);

public __gc __interface IAManagedInterface {
	void MethodA();
	int MethodB();
};

public __gc class AManagedClass : public IAManagedInterface {

	int m_n;
	int m_nSize;
	double m_f;
	String *m_str;

	DaysOfTheWeek m_DayOfWeek;
	ArrayList *m_rgManagedArray;

public:

	AManagedClass() {
		m_str = new String("This is AManagedClass\n");
		m_DayOfWeek = Friday;
	}

	~AManagedClass() {
		System::Console::WriteLine("AManagedClass going away\n");
	}

	__property int  get_Size() {
		return m_nSize;
	}

	__property void set_Size(int value) {
		m_nSize = value;
	}

	void MethodA() {
		Console::WriteLine("Here's some managed C++ code. This is MethodA.");
	}

	int MethodB()  {
		Console::WriteLine("Here's some managed C++ code. This is MethodB.");
		return 0;
	}

	void FillArray() {
		m_rgManagedArray = new ArrayList();

		Console::WriteLine("Creating a DotCOMVP");
		m_rgManagedArray->Add(new DotCOMVP());
		Console::WriteLine("Creating a Bum");
		m_rgManagedArray->Add(new Bum());
		Console::WriteLine("Creating a Software Developer");	
		m_rgManagedArray->Add(new SoftwareDeveloper());
	}


	void ShowArray() {
		Console::WriteLine();	
		if(m_rgManagedArray) {
			for(int i = 0; i < m_rgManagedArray->Count; i++) {
				Console::Write("Type: ");
				Console::WriteLine((m_rgManagedArray->get_Item(i))->GetType()->ToString());
				IPerson* person;
				person = __try_cast<IPerson*>(m_rgManagedArray->get_Item(i));
				person->Eat();
				person->Work();
				person->Sleep();
				Console::WriteLine();	
			}
		}
	}

	void UseDelegate(AManagedDelegate *d) {
		d->Invoke("This is called through the delegate...");
	}

};

}
