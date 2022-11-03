// Ex34c.h

#pragma once

#using <system.dll>
#using <system.web.dll>
using namespace System;
using namespace System::Web;
using namespace System::IO;
namespace Ex34c
{
public __gc class SourceCodeHandler :
	public IHttpHandler
	{
		void ProcessRequest(HttpContext* context)
		{
			context->Response->Write("Viewing file: ");
			context->Response->Write(context->Request->PhysicalPath);
			context->Response->Write("<br>");
			try 
			{
				StreamReader* sr;
				sr = new StreamReader(context->Request->PhysicalPath);
				String* str;
				do
				{
					str = sr->ReadLine();
					context->Response->Write("<p>");
					context->Response->Write(str);
					context->Response->Write("</p>");
				} while (str != 0);
			}
			catch (FileNotFoundException* )
			{
				context->Response->Write("<h2>Sorry - the log you requested is not available</h2>");
			}
		}

		__property bool get_IsReusable() 
		{
		  return true; 
		}
	};
}
