<%@ Page Language="c#" Inherits="Ex34a.ManagedCPPPage" %>

<html>
<body>
<form runat=server>

<h3> Favorite .NET Features </h3>

<% DisplayFeatures(); %>

  </br>
  <asp:Label text="Type your name:" runat=server />
  <asp:TextBox id="m_name" runat=server/> </br> </br>
  <asp:Label Text="Select your favorite .NET feature:" runat=server /> </br>
  <asp:CheckBoxList id="m_cblFeatureList" runat=server/> </br></br>
  <asp:Button id="Submit" OnClick="SubmitInfo" Text="Submit" runat=server /> </br>
  <asp:Label id="m_labelInfo" runat=server />
  

</form>
</body>
</html>


