// ManagedCWebForm.h

#pragma once

using namespace System;
#using <System.Dll>
#using <System.Web.dll>

using namespace System;
using namespace System::Web;
using namespace System::Web::UI;
using namespace System::Web::UI::WebControls;
using namespace System::Collections;
using namespace System::ComponentModel;

namespace [!output PROJECT_NAME]
{
public __gc class [!output PROJECT_NAME]Page : public Page 
{
    public:

[!if UseLabel]
        Button* m_button;
[!endif]

[!if UseLabel]
        Label* m_label;
[!endif]
[!if UseTextBox]
        TextBox* m_text;
[!endif]
[!if UseCheckBox]
        CheckBox* m_check;
[!endif]

        [!output PROJECT_NAME]Page() 
        {
            // To do: Construction code here...
        }

        void SubmitEntry(Object* o, EventArgs* e) 
        {
            // Called when Submit button pressed
            // To do: insert Page Loading code here...
            String* str;

            str = new String("Hello ");
            str = str->Concat(str, m_text->get_Text());
            str = str->Concat(str, new String(" you pushed Submit"));

[!if UseLabel]
            m_label->set_Text(str);
[!endif]
        }

        void Page_Load(Object* o, EventArgs* e)
        {
            // To do: insert Page Loading code here...
[!if UsePageTracing]
            Trace->Write("Custom", "Inside Page_Load"); 
[!endif]
            if(!IsPostBack) {
            } 
        }
    };
}
