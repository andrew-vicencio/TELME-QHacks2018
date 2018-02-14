$(document).ready( function(){
  var myAPI = "8B18mZhs2uqttEfDJ95xx7PTk8bohh7n";
  var serverURL = "http://http://localhost:8080/";
  var mlabURL = "https://api.mlab.com/api/1";
  var getURL = "/databases/convodb/collections";
  var textURL = "/getDataText";
  var AnalysisURL = "/getDataAnalysis";

  var text;
  var analysis;
  $.ajax ( serverURL, {
    type: "GET",
    async: true,
    success: function(data){
      text = data;
      console.log("FUCK YES");
      console.log(data);
    },
    error: function(xhr, status, error){
      console.log("FUCK OFF");
      err = eval("(" + xhr.responseText + ")");
      alert(err.Message);
    },
    complete: function(){
      console.log("It finished but not really");
    }
  });
});

  /*$.ajax( mlabURL+getURL+textURL,
          {type: "GET",
          data: myAPI,
          contentType: "text",
          dataType: "application/json",
          success: function(data){
            console.log("YES");
            console.log(data);
          },
          xhrFields: {
            withCredentials: true
          },
          data: {
            "apiKey":myAPI
          }
        });*/

  /*$.get(serverURL, function(data){
    text = data;
    console.log("text received");
  });

  $.get(serverURL, function(data){
    analysis = data;
    console.log("text received");
  });*/
