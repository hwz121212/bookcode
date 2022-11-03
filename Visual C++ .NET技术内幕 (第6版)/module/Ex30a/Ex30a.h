// Ex30a.h : Defines the ATL Server request handler class
//
#pragma once

[ request_handler("Default") ]
class CEx30aHandler
{
private:
	// Put private members here
	// uncomment the service declaration(s) if you want to use
	// a service that was generated with your ISAPI extension

	// Session service support
//	CComPtr<ISessionStateService> m_spSessionSvc;
//	CComPtr<ISession> m_spSession;

protected:
	// Put protected members here

public:
	// Put public members here

	HTTP_CODE ValidateAndExchange()
	{
		// TODO: Put all initialization and validation code here
		
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");

		// uncomment the service initialization(s) if you want to use
		// a service that was generated with your ISAPI extension
		

		// Get the ISessionStateService from the ISAPI extension
	
		return HTTP_SUCCESS;
	}
 
protected:
	// Here is an example of how to use a replacement tag with the stencil processor
	[ tag_name(name="Hello") ]
	HTTP_CODE OnHello(void)
	{
		m_HttpResponse << "Hello World!";
		return HTTP_SUCCESS;
	}

	[ tag_name(name="PersonalGreeting") ]
	HTTP_CODE OnPersonalGreeting(void)
	{
		const CHttpRequestParams& FormFields = m_HttpRequest.GetFormVars();

		LPCSTR szName = FormFields.Lookup("Name");
		if(szName) {
			m_HttpResponse << "You are " << szName;
		} else {
			m_HttpResponse << "I don't know you.";
		}
		return HTTP_SUCCESS;
	}

}; // class CEx30aHandler
