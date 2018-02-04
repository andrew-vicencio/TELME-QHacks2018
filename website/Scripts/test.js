$(document).ready( function(){
  var myAPI = "8B18mZhs2uqttEfDJ95xx7PTk8bohh7n";
  var serverURL = "https://thawing-tundra-20039.herokuapp.com";
  var mlabURL = "https://api.mlab.com/api/1";
  var getURL = "/databases/convodb/collections";
  var textURL = "/Text";
  var AnalysisURL = "/Analysis";

  var text;
  var analysis;

  $.ajax( mlabURL+getURL+textURL,
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
        });

  $.get(serverURL, function(data){
    text = data;
    console.log("text received");
  });

  $.get(serverURL, function(data){
    analysis = data;
    console.log("text received");
  });
});
