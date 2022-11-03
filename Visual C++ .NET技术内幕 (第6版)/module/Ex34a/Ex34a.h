// Ex34a.h

#pragma once

#using <system.dll>
#using <system.web.dll>
using namespace System;
using namespace System::Web;
using namespace System::Web::UI;
using namespace System::Web::UI::WebControls;
using namespace System::Collections;
using namespace System::ComponentModel;


namespace Ex34a
{
	public __gc class ManagedCPPPage : public Page
	{
	protected:
		ArrayList* m_arrayList;
		CheckBoxList* m_cblFeatureList;
		Label* m_labelInfo;
		TextBox* m_name;

		void AssembleChoices()
		{
			m_arrayList = new ArrayList();
			String* str = "Just-in-time compiling";
			m_arrayList->Add(str);
			str = "Common runtime environment";
			m_arrayList->Add(str);
			str = "Multiple language support";
			m_arrayList->Add(str);
			str = "Simplified component model";
			m_arrayList->Add(str);
			str = "Excellent backward compatibility";
			m_arrayList->Add(str);
			str = "ASP.NET";
			m_arrayList->Add(str);
		}
		void DisplayFeatures() 
		{
			for(int i = 0; i < m_arrayList->Count; i++)
			{
				Response->Write("<li>");
				Response->Write(m_arrayList->get_Item(i));
				Response->Write("</li>");
			}
		}

		void Page_Load(Object* o, EventArgs* ea) 
		{
			AssembleChoices();
			if(!this->IsPostBack)
			{
				m_cblFeatureList->DataSource = m_arrayList;
				m_cblFeatureList->DataBind();

			}
		}
		void SubmitInfo(Object* o, EventArgs* ea)
		{
			String* s;

			s = s->Concat(S"Hello ", m_name->Text);
			s = s->Concat(s, S". You selected ");
            for(Int32 i = 0; 
                i < m_cblFeatureList->Items->get_Count(); i++)
            {
                if(m_cblFeatureList->Items->get_Item(i)->get_Selected())
                {
                    s = s->Concat(s, S"<li>");
                    s = s->Concat(s, m_cblFeatureList->Items->
                        get_Item(i)->get_Text());  
                        s = s->Concat(s, S"</li>");
                }
            }
			s = s->Concat(s, S"</br>");
			s = s->Concat(s, S" as your favorite .NET feature");

			m_labelInfo->Text=s;
		}
	};
}
