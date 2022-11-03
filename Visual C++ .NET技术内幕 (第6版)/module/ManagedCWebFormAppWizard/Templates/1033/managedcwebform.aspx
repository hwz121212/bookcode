<%@ Page Language="C#" 
[!if UseRequestTracing]
  Trace=true
[!endif]
  Inherits="[!output PROJECT_NAME].[!output PROJECT_NAME]WebPage" 
%>

<html>
<body>
<form runat=server>
<h2>ASP.NET Web Form</h2>

<br><br><br>

  <asp:Button Text="Sumit Entry" id="m_button" 
    OnClick="SubmitEntry" runat=server /><br/>

  <asp:Label Text="Type your name here" runat=server />


[!if UseTextBox]
  <asp:TextBox id="m_text" runat=server /><br/>
[!endif]

[!if UseCheckBox]
  <asp:CheckBox id="m_check" runat=server /> <br/>
[!end]

[!if UseLabel]
  <asp:Label id="m_label" runat=server />
[!endif]

</form>
</body> 
</html>
