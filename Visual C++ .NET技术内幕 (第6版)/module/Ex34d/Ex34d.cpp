#include "stdafx.h"
#include "Ex34d.h"
#include "Global.asax.h"

namespace Ex34d
{


    String __gc* Class1::HelloWorld()
    {

		// TODO: Add the implementation of your Web Service here

		return S"Hello World!";
        
    }

	int Class1::Add(int x, int y)
	{
		return x+y;
	}

	int Class1::Subtract(int x, int y)
	{
		return x-y;
	}

};
