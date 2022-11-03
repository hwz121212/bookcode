<%@ Language="javascript" %>

<html><body>
    Feature: <select name="Feature">
	  <option
		  <% if (Request("Feature") == "Garbage collection") {
		  Response.Write("selected");
		  }%> >Garbage collection</option>
	  <option
		  <% if (Request("Feature") == "Multiple languages") {
		       Response.Write("selected");
		  }%> >Multiple languages</option>
	  <option
		  <% if (Request("Feature") == "No more GUIDS") {
		       Response.Write("selected");
		  }%> >No more GUIDS</option>
		  
      </select>
  
</body></html>
