// Ex34d.h

#pragma once

#using <System.Web.Services.dll>

using namespace System;
using namespace System::Web;
using namespace System::Web::Services;

namespace Ex34d
{
    public __gc 
        class Class1 : public WebService
    {
        
    public:
        [System::Web::Services::WebMethod] 
        String __gc* HelloWorld();
        [System::Web::Services::WebMethod] 
        int Add(int x, int y);
        [System::Web::Services::WebMethod] 
        int Subtract(int x, int y);
    };
}
