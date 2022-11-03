// Ex34b.h

#pragma once


#using <system.dll>
#using <system.web.dll>
using namespace System;
using namespace System::Web;

namespace Ex34b
{
public __gc class RejectRequestModule : 
	public IHttpModule
	{
		bool m_bRejectRequest;
	public:
		RejectRequestModule() 
		{
			m_bRejectRequest = false;
		}
      void Init(HttpApplication* httpApp) {
		httpApp->
			add_BeginRequest(new EventHandler(this, OnBeginRequest));   
		httpApp->
			add_EndRequest(new EventHandler(this, OnEndRequest));
      }

      void Dispose() {
         // Usually, nothing has to happen here...
      }

      // Event handlers   
      void OnBeginRequest(Object* o, EventArgs* ea) {
         HttpApplication* httpApp = dynamic_cast<HttpApplication*>(o);   
         HttpContext* ctx;
		 ctx = HttpContext::Current;
         ctx->Response->Write("Beginning Request <br>");
         ctx->Response->Write("URL Used to surf here: ");
         ctx->Response->Write(ctx->Request->Url);
         ctx->Response->Write("<br>");
         ctx->Response->Write("Authenticated? ");
         ctx->Response->Write(ctx->Request->IsAuthenticated.ToString());
         ctx->Response->Write("<br>");
         ctx->Response->Write("Using secure connection? ");
         ctx->Response->Write(ctx->Request->IsSecureConnection.ToString());
         ctx->Response->Write("<br>");
		 if(m_bRejectRequest) {
	         ctx->Response->Write("<br>Stopping every other request...<br>");
			 httpApp->CompleteRequest();
			 ctx->Response->StatusCode = 500;
			 ctx->Response->StatusDescription = 
				 "Server Error";
		 }
		 m_bRejectRequest = !m_bRejectRequest;
      }

      void OnEndRequest(Object* o, EventArgs* ea) {
         HttpApplication* httpApp = dynamic_cast<HttpApplication*>(o);   
		 HttpContext* ctx = HttpContext::Current;

         ctx->Response->Write("<br>");
         ctx->Response->Write("Ending Request <br>");

      }

	};
}
